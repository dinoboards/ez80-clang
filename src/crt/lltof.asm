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
	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__lltof, __lltod
__lltof:
__lltod:
	push	af
	push	iy
	push	bc
	push	de
	push	hl
	call	__lltof_c
	pop	af
	pop	af
	pop	af
	pop	iy
	pop	af
	ret

	extern	__lltof_c
