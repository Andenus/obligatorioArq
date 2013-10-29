#asm
	inicilizarIntsInt::
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


   int1_isr::
   	ioi ld A, (PEDR)
      bit 1,A
      jp z, fila1
      bit 5,A
      jp z, fila3
      int0ret::
      	call delay
      	ipres
      	ret

   int0_isr::
   	ioi ld A, (PEDR)
      bit 0,A
      jp z, fila0
      bit 4,A
      jp z, fila2
      int1ret::
         call delay
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
      	ld E,0x00
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int0ret

      boton01:
      	ld E,0x01
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int0ret

      boton02:
      	ld E,0x02
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int0ret

      boton03:
      	ld E,0x03
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int0ret

      boton04:
      	ld E,0x04
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int0ret

      boton05:
      	ld E,0x05
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int1ret

      boton06:
      	ld E,0x06
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int1ret

      boton07:
      	ld E,0x07
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int1ret

   	boton08:
      	ld E,0x08
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int0ret

      boton09:
      	ld E,0x09
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int0ret

      boton0A:
      	ld E,0x0A
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int0ret

      boton0B:
      	ld E,0x0B
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int0ret

   	boton0C:
      	ld E,0x0C
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int1ret

      boton0D:
      	ld E,0x0D
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int1ret

      boton0E:
      	ld E,0x0E
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int1ret

      boton0F:
      	ld E,0x0F
         call switchluz
         ld A,0x00
         ioi ld (PEDR), A
         jp int1ret





   delay::
      	push BC                   ;10
	      ld D, 0x02                ;4
	      loop0:
	         ld B, 0x00             ;4
	         loop1:
	            ld C, 0x00          ;4
	            loop2:
	               nop              ;2
                  nop              ;2
	               dec C            ;2
	               jp NZ, loop2     ;7
	            djnz loop1          ;5
	         dec D                  ;2
	         jp NZ, loop0           ;7
         pop BC                    ;7
	      ret

#endasm