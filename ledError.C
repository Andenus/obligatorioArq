/*** BeginHeader ledError */
void ledError (void);
/*** EndHeader */
#asm
	ledError::
   	ld A,0x0F
      ioi ld (PDDDR),A
      ld B, 0x0A
      call loop
      ret

   loop::
   	ld A,0x0F
      ioi ld (PDDR),A
      call delay
      ld A, 0x00
      ioi ld (PDDR),A
      call delay
		djnz loop
      ret

   delay::
   	push BC
   	ld D, 0x20
      loop0:
      	ld B, 0x80  ;AA
	      loop1:
	         ld C, 0x30  ;CC
	         loop2:
	            nop
               srl(IX+2)
	            dec C
	            jr NZ, loop2
	         djnz loop1
         dec D
         jr NZ, loop0
      pop BC
      ret


#endasm