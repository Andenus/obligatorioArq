#use DISPLAYobligatorio.C
#use ledError.C
char barco1;
char barco21;
char barco22;
char barco31;
char barco32;
char barco33;

#asm
   main::
   	call iniciaDisplay
   	ld A, 00001111b
      ioi ld (PDDDR), A
      ld A, 11001100b
     	ioi ld (PEDDR), A
      ld HL, int0_isr
      push HL
      ld HL, 0x0000
      push HL
      call SetVectExtern3000
      nop
      add sp,4
      ld HL, int1_isr
      push HL
      ld HL, 0x0001
      push HL
      call SetVectExtern3000
      nop
      add sp,4
      ld A, 00010110b
      ioi ld (I0CR), A
      ioi ld (I1CR), A
      ld H, 0x01

   stop::
   	jp stop

   int1_isr::
   	ioi ld A, (PEDR)
      bit 1,A
      jp z, fila1
      bit 5,A
      jp z, fila3
      int0ret::
      	call delayBotones
      	ipres
      	ret

   int0_isr::
   	ioi ld A, (PEDR)
      bit 0,A
      jp z, fila0
      bit 4,A
      jp z, fila2
      int1ret::
         call delayBotones
      	ipres
      	ret

   fila0:
      ld A,11001000b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 0,A
      jp z,boton0C
      ld A,11000100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 0,A
      jp z,boton0D
      ld A,10001100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 0,A
      jp z,boton0E
      ld A,01001100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 0,A
      jp z,boton0F

   fila1:
      ld A,11001000b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 1,A
      jp z,boton08
      ld A,11000100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 1,A
      jp z,boton09
      ld A,10001100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 1,A
      jp z,boton0A
      ld A,01001100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 1,A
      jp z,boton0B

   fila2:
      ld A,11001000b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 4,A
      jp z,boton04
      ld A,11000100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 4,A
      jp z,boton05
      ld A,10001100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 4,A
      jp z,boton06
      ld A,01001100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 4,A
      jp z,boton07

   fila3:
      ld A,11001000b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 5,A
      jp z,boton00
      ld A,11000100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 5,A
      jp z,boton01
      ld A,10001100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 5,A
      jp z,boton02
      ld A,01001100b
      ioi ld (PEDR), A
      ioi ld A,(PEDR)
      bit 5,A
      jp z,boton03

   switchluz:
	   ld A,E
	   ioi ld (PDDR),A
	   ret

	boton00:
      call mal
      jp int0ret

   boton01:
      call mal
      jp int0ret

   boton02:
      call mal
      jp int0ret

   boton03:
      call mal
      jp int0ret

   boton04:
      call mal
      jp int1ret

   boton05:
      call mal
      jp int1ret

   boton06:
      call mal
      jp int1ret

   boton07:
      call mal
      jp int1ret

   boton08:
   	call mal
      jp int0ret

   boton09:
      call mal
      jp int0ret

	boton0A:
   	ld B, 00000000b
  		call checkearPrimeraFase
      jp int0ret

	boton0B:
   	ld B, 00100000b
   	call checkearPrimeraFase
      jp int0ret

	boton0C:
   	ld B, 01000000b
      call checkearPrimeraFase
      jp int1ret

	boton0D:
   	ld B, 01100000b
     	call checkearPrimeraFase
      jp int1ret

	boton0E:
      call mal
      jp int1ret

   boton0F:
		call mal
      jp int1ret

	checkearPrimeraFase::
   	ld A,0x01
      cp H
      jp z,bien
      jp mal
      retCheckearPrimeraFase:
      	ret


	delayBotones:
	   push BC                   ;10
	   ld D, 0x02                ;4
	   loop0Botones:
	      ld B, 0x00             ;4
	      loop1Botones:
	         ld C, 0x00          ;4
	         loop2Botones:
	            nop              ;2
	            nop              ;2
	            dec C            ;2
	            jp NZ, loop2Botones     ;7
	         djnz loop1Botones          ;5
	      dec D                  ;2
	      jp NZ, loop0Botones           ;7
	   pop BC                    ;7
	   ret



   mal::
   	call ledError
		jp retCheckearPrimeraFase

   bienPrimeraFase::
      ld A, H
      add A, 0x01
      ld H, A
      ld A, B
      ioi ld (barco1), A
      jp retCheckearPrimeraFase


#endasm