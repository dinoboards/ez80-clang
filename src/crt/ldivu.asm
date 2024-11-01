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
	.global	__ldivu

__ldivu:
; I: EUHL=dividend, AUBC=divisor
; O: euhl=EUHL/AUBC

	push	bc

	call	__ldvrmu

	ld	a, b
	pop	bc

	ret	z
	ei
	ret

	extern	__ldvrmu
