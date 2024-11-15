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
	.global	__lremu

__lremu:
; I: EUHL=dividend, AUBC=divisor
; O: euhl=EUHL%AUBC

	call	__ldvrmu
	ld	e, a
	push	de
	exx
	ld	a, e
	pop	de

	ret	z
	ei
	ret

	extern	__ldvrmu
