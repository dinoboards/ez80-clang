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
	.global	_div
_div:
	pop	de
	pop	iy
	pop	hl
	pop	bc
	push	de
	push	de
	push	de
	push	de

	call	__idvrms
	ld	(iy), hl
	ld	(iy + 3), de

	ret

	extern	__idvrms
