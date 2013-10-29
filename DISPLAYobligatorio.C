/*** BeginHeader iniciaDisplay */
void iniciaDisplay (void);
/*** EndHeader */

#asm
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
#endasm


#asm
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
    	ld C, 0xA8          ;4
   	loop2:
			nop              ;2
			dec C            ;2
		jp NZ, loop2        ;7
      ret

   delay5ms::
   	ld B, 0x32
      loop5ms1::
      	call delay100us
         dec D
         djnz loop5ms1
      ret

   delay15ms::
   	ld E, 0x03
      loop15ms::
      	call delay5ms
         dec E
         jp NZ, loop15ms
      ret

   delayinst::
   	ld D, 0xB0
      loopdelayinst::
      	call delay100us
         dec D
         jp NZ, loop5ms1
      ret





   cursorshift::
   	push BC
   	ld A, 00100001b
      call send
      ld A, 00100100b
      call send
      pop BC
      ret

#endasm