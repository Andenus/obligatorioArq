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
      ld E, 0x00
      ld D, 0x01

   setBarcos::
   	ld A, 0x03
      cp E
      jp z, agregarBarco
   	jp setBarcos

   agregarBarco::
   	ld A, 0x01
      cp D
      jp z, agBarco31
      ld A, 0x02
      cp D
      jp z, agBarco32
      ld A, 0x03
      cp D
      jp z, agBarco33
      ld A, 0x04
      cp D
      jp z, agBarco21
      ld A, 0x05
      cp D
      jp z, agBarco22
      ld A, 0x06
      cp D
      jp z, agBarco1

   agBarco31::
   	ld A, B
      ld (barco31), A
      ld A, D
      add A, 0x01
      ld D, A
      ld E, 0x00
      ld A, 01100011b
      call send
      ld A, 01100001b
      call send
      jp stop

   agBarco32::
   	ld A, B
      ld (barco32), A
      ld A, D
      add A, 0x01
      ld D, A
      ld E, 0x00
      ld A, 01100011b
      call send
      ld A, 01100010b
      call send
      jp stop

   agBarco33::
   	ld A, B
      ld (barco33), A
      ld A, D
      add A, 0x01
      ld D, A
      ld E, 0x00
      ld A, 01100011b
      call send
      ld A, 01100011b
      call send
      jp stop

   agBarco21::
   	ld A, B
      ld (barco21), A
      ld A, D
      add A, 0x01
      ld D, A
      ld E, 0x00
      jp stop

   agBarco22::
   	ld A, B
      ld (barco22), A
      ld A, D
      add A, 0x01
      ld D, A
      ld E, 0x00
      ld A, 01100011b
      call send
      ld A, 01100010b
      call send
      jp stop

   agBarco1::
   	ld A, B
      ld (barco1), A
      ld A, D
      add A, 0x01
      ld D, A
      ld E, 0x00
      ld A, 01100011b
      call send
      ld A, 01100001b
      call send
      jp comienzo

   comienzo::
   	ld A, 0x00
	   ioi ld (SACR), A
	   ld A, 11111100b
	   ioi ld (TACR), A
	   ld A, 0x3B
	   ioi ld (TAT4R), A
	   ld A, 00000001b
	   ioi ld (TACSR), A
      ld A, 01000000b
      ioi ld (PCFR),A
      ioi ld A, (SASR)
      bit 7, A
      jp nz, segundoJugador
      jp primerJugador

   primerJugador::
   	ioi ld (SADR), A
      ioi ld A, (SASR)
      bit 7, A
      jp z, primerJugador
      ioi ld A, (SADR)
      cp 0x53
      jp z, turno
      jp primerJugador

   segundoJugador::
   	ld A, 0x53
   	ioi ld (SADR), A
      jp noTurno

   noTurno::
      call esperar
      ld C,0x41
      sub 0x41
      ld D, A
      rlc D
      call esperar
      sub 0x30
      add A, D
      ld D, A
      rlc D
      rlc D
      rlc D
      rlc D
      call esperar
      sub 0x30
      add A,D
      ld D, A
		ld A, (barco1)
      cp D
      jp z, barco1Hun
      ld A, (barco21)
      cp D
      jp z, barco21Toc
      ld A, (barco22)
      cp D
      jp z, barco22Toc
      ld A, (barco31)
      cp D
      jp z, barco31Toc
      ld A, (barco32)
      cp D
      jp z, barco32Toc
      ld A, (barco33)
      cp D
      jp z, barco33Toc
      jp sendH2O


   turno::
   	ld A, 0x03
      cp E
      jp z, enviarCoordenada
   	jp turno

   enviarCoordenada::


   barco1Hun::
   	ld A, (barco1)
      add A, 10000000b
      call sendHun
      jp turno

   barco21Toc::
   	ld A, (barco21)
      add A, 10000000b
      ld (barco21), A
      jp verificBar2Hun

   barco22Toc::
   	ld A, (barco22)
      add A, 10000000b
      ld (barco22), A
      jp verificBar2Hun

   barco31Toc::
   	ld A, (barco31)
      add A, 10000000b
      ld (barco31), A
      jp verificBar3Hun

   barco32Toc::
   	ld A, (barco32)
      add A, 10000000b
      ld (barco32), A
      jp verificBar3Hun

   barco33Toc::
   	ld A, (barco33)
      add A, 10000000b
      ld (barco33), A
      jp verificBar3Hun

   verificBar2Hun::
   	ld A, (barco21)
      bit 7, A
      jp z, sendToc
      ld A, (barco22)
      bit 7, A
      jp z, sendToc
      jp sendHun

   verificBar3Hun::
   	ld A, (barco31)
      bit 7, A
      jp z, sendToc
      ld A, (barco32)
      bit 7, A
      jp z, sendToc
      ld A, (barco33)
      bit 7, A
      jp z, sendToc
      jp sendHun

	sendToc::
	   ioi ld A,(SASR)
	   bit 2, A
	   jp nz, sendToc
	   ld A, 0x54
	   ioi ld (SADR), A
	   call delay100us
	   ld A, 0x4F
	   ioi ld (SADR), A
	   call delay100us
	   ld A, 0x43
	   ioi ld (SADR), A
	   call delay100us
      jp turno

	sendHun::
      ioi ld A,(SASR)
      bit 2, A
      jp nz, sendHun
      ld A, 0x48
	   ioi ld (SADR), A
      call delay100us
      ld A, 0x55
	   ioi ld (SADR), A
      call delay100us
      ld A, 0x4E
	   ioi ld (SADR), A
      call delay100us
      jp turno

   sendH2O::
      ioi ld A,(SASR)
      bit 2, A
      jp nz, sendH2O
      ld A, 0x48
	   ioi ld (SADR), A
      call delay100us
      ld A, 0x32
	   ioi ld (SADR), A
      call delay100us
      ld A, 0x4F
	   ioi ld (SADR), A
      call delay100us
      jp turno



   int1_isr::
   	ioi ld A, (PEDR)
      bit 1,A
      jp z, fila1
      bit 5,A
      jp z, fila3
      int1ret::
      	ld A,00000000b
      	ioi ld (PEDR), A
      	call delayBotones
      	ipres
      	ret

   int0_isr::
   	ioi ld A, (PEDR)
      bit 0,A
      jp z, fila0
      bit 4,A
      jp z, fila2
      int0ret::
         ld A,00000000b
      	ioi ld (PEDR), A
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
      ld A, B
      add A, 00000000b
      ld B, A
      ld A, E
      add A, 0x01
      ld E, A
      ld A, 01100011b
      call send
      ld A, 01100000b
      call send
      jp retBoton00y01

   boton01:
      ld A,0x02
      cp E
      jp z, sumaSegunda1
      ld A, B
      add A, 00000001b
      ld B,A
      ld A, E
      add A, 0x01
      ld E, A
      ld A, 01100011b
      call send
      ld A, 01100001b
      call send
      jp retBoton00y01

   sumaSegunda1::
   	ld A, 01100011b
      call send
      ld A, 01100001b
      call send
      ld A, B
      add A, 00010000b
      ld B,A
      ld A, E
      add A, 0x01
      ld E, A
      jp int1ret

   retBoton00y01::
   	jp int1ret

   boton02:
      ld A, 01100011b
      call send
      ld A, 01100010b
      call send
      ld A, B
      add A, 00000010b
      ld B,A
      ld A, E
      add A, 0x01
      ld E, A
      jp int1ret

   boton03:
      ld A, 01100011b
      call send
      ld A, 01100011b
      call send
      ld A, B
      add A, 00000011b
      ld B,A
      ld A, E
      add A, 0x01
      ld E, A
      jp int1ret

   boton04:
      ld A, 01100011b
      call send
      ld A, 01100100b
      call send
      ld A, B
      add A, 00000100b
      ld B,A
      ld A, E
      add A, 0x01
      ld E, A
      jp int0ret

   boton05:
      ld A, 01100011b
      call send
      ld A, 01100101b
      call send
      ld A, B
      add A, 00000101b
      ld B,A
      ld A, E
      add A, 0x01
      ld E, A
      jp int0ret

   boton06:
      ld A, 01100011b
      call send
      ld A, 01100110b
      call send
      ld A, B
      add A, 00000110b
      ld B,A
      ld A, E
      add A, 0x01
      ld E, A
      jp int0ret

   boton07:
      ld A, 01100011b
      call send
      ld A, 01100111b
      call send
      ld A, B
      add A, 00000111b
      ld B,A
      ld A, E
      add A, 0x01
      ld E, A
      jp int0ret

   boton08:
      ld A, 01100011b
      call send
      ld A, 01101000b
      call send
      ld A, B
      add A, 00001000b
      ld B,A
      ld A, E
      add A, 0x01
      ld E, A
      jp int1ret

   boton09:
      ld A, 01100011b
      call send
      ld A, 01101001b
      call send
      ld A, B
      add A, 00001001b
      ld B,A
      ld A, E
      add A, 0x01
      ld E, A
      jp int1ret

	boton0A:
      ld A, 01100100b
      call send
      ld A, 01100001b
      call send
   	ld B, 00000000b
      ld A, E
      add A, 0x01
      ld E, A
      jp int1ret

	boton0B:
      ld A, 01100100b
      call send
      ld A, 01100010b
      call send
   	ld B, 00100000b
      ld A, E
      add A, 0x01
      ld E, A
      jp int1ret

	boton0C:
      ld A, 01100100b
      call send
      ld A, 01100011b
      call send
   	ld B, 01000000b
      ld A, E
      add A, 0x01
      ld E, A
      jp int0ret

	boton0D:
      ld A, 01100100b
      call send
      ld A, 01100011b
      call send
   	ld B, 01100000b
      ld A, E
      add A, 0x01
      ld E, A
      jp int0ret

	boton0E:
      call mal0
      jp int0ret

   boton0F:
		call mal0
      jp int0ret

   mal0::
	   call ledError
	   ret


   delayBotones:
	   push BC                   ;10
      push DE
	   ld D, 0x04                ;4
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
      pop DE
	   pop BC                    ;7
	   ret

	iniciaDisplay::
	   ld A, 10000100b
	   ioi ld (SPCR), A
	   call delay15ms
	   ld A, 00100010b      ;Function set
	   ioi ld (PADR), A
	   ld A, 00000010b      ;Function set
	   ioi ld (PADR), A
	   call delay5ms
	   ld A, 00100010b      ;Function set
	   ioi ld (PADR), A
	   ld A, 00000010b      ;Function set
	   ioi ld (PADR), A
	   call delay100us
	   ld A, 00101000b      ;Function set
	   call send
	   ld A, 00100000b      ;Display off
	   call send
	   ld A, 00101000b      ;Display off
	   call send
	   ld A, 00100000b      ;Clear display
	   call send
	   ld A, 00100001b      ;Clear display
	   call send
	   ld A, 00100000b      ;Entry mode set
	   call send
	   ld A, 00100110b      ;Entry mode set
	   call send
	   ld A, 00100000b      ;Display on, cursor on, bilnking off
	   call send
	   ld A, 00101110b      ;Display on, cursor on, bilnking off
	   call send
	   ret

	send::
	   push BC
	   ioi ld (PADR),A
	   ld B, 00100000b
	   sub B
	   ioi ld (PADR),A
	   call delayinst
	   pop BC
	   ret

	delay100us::
	   push BC
	   ld C, 0xA8          ;4
	   loop2:
	      nop              ;2
	      dec C            ;2
	      jp NZ, loop2        ;7
      pop BC
      ret

	delay5ms::
	   push BC
	   push DE
	   ld B, 0x32
	   loop5ms1::
	      call delay100us
	      dec D
	      djnz loop5ms1
	   pop DE
	   pop BC
	   ret

	delay15ms::
	   push DE
	   ld E, 0x03
	   loop15ms::
	      call delay5ms
	      dec E
	      jp NZ, loop15ms
      pop DE
      ret

	delayinst::
	   push DE
	   ld D, 0xB0
	   loopdelayinst::
	      call delay100us
	      dec D
	      jp NZ, loop5ms1
      pop DE
      ret
#endasm