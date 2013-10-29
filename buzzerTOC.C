#asm
   main::
   	ld A, 00001000b
      ioi ld (GCSR), A
      ld HL, buzzer
      push HL
      ld HL, 0x000A
      push HL
      call SetVectIntern
      nop
      add sp,4
      ld A, 11111110b
      ioi ld (TACR), A
      ld A, 0xFF
      ioi ld (TAT1R), A
      ld A, 0x05
      ioi ld (TAT4R), A
      ld A, 00010001b
      ioi ld (TACSR), A
      delay250ms::
         ld D, 0x32
      	loop250ms::
      		call delay5ms
         	dec D
         	jp NZ, loop250ms
      ld A, 00000001b
      ioi ld (TACSR), A

      stop:
      	ld A, 0x5A          ;4
      	ioi ld (WDTCR), A
   		jr stop




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





	buzzer::
      ioi ld A, (PCDR)    ;9
      xor 0x01            ;2
   	ioi ld (PCDR), A    ;9
      ioi ld A, (TACSR)   ;9
      ipres               ;4
      ret                 ;8





#endasm