;--------------------------------------------------------------
;
;	C RUNTIME FUNCTION
;	For the eZ80 Clang cross compiler
;
;  Original file source: https://github.com/CE-Programming/toolchain
;  License: https://github.com/CE-Programming/toolchain?tab=LGPL-3.0-1-ov-file
;
; Modified to comply with GNU AS assembler (ez80-none-elf-as) syntax
;
;--------------------------------------------------------------
	.assume adl=1

	section	.text,"ax",@progbits
	.global	__frameset0

__frameset0:
	pop	hl
	push	ix
	ld	ix,0
	add	ix,sp
	jp	(hl)
