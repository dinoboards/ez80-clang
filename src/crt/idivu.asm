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
; Performs 16-bit unsigned division
; Arguments: uhl = dividend, ubc = divisor
; Result: uhl
;--------------------------------------------------------------
	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__idivu

__idivu:
	push	de

	call	__idvrmu
	ex	de, hl

	pop	de
	ret

	extern	__idvrmu
