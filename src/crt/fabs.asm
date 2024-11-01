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
	.global	_fabs, _fabsf

_fabs:
_fabsf:
	pop	bc
	pop	hl
	pop	de
	push	de
	push	hl
	push	bc
	res	7,e
	ret
