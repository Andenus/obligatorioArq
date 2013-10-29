char barco1;

#asm
	main::
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
      call esperar
      ld C,0x41
      sub 0x41
      ld D, A
      rlc D
      ld A,00100010b
      ioi ld (barco1),A


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


      loop2::
      ioi ld A,(SASR)
      bit 2, A
      jp nz, loop2
      ioi ld A,(barco1)
      ld H,A
      ld A, D
      cp H
      jp z,hundido

      loop::
      jp loop

   esperar::
      ioi ld A, (SASR)
      bit 7, A
      jp z, esperar
      ioi ld A, (SADR)
      ret

	hundido::
      ld A, 0x48
   	ioi ld (SADR), A
      ld A, 0x55
      ioi ld (SADR), A
      ld A, 0x4E
      ioi ld (SADR), A

#endasm








