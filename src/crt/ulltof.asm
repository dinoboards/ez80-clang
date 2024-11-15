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

	section	.text,"ax",@progbits
	.global	__ulltof, __ulltod
__ulltof:
__ulltod:
	push	af
	push	iy
	push	bc
	push	de
	push	hl
	call	__ulltof_c
	pop	af
	pop	af
	pop	af
	pop	iy
	pop	af
	ret

	extern	__ulltof_c
