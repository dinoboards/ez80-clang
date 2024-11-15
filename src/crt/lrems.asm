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
	.global	__lrems

__lrems:
; I: EUHL=dividend, AUBC=divisor
; O: euhl=EUHL%AUBC

	bit	7, e
	push	af
	push	bc

	call	__ldivs_lrems_common

	call	__lremu

	pop	bc
	pop	af
	ret	z
	jp	__lneg

	extern	__ldivs_lrems_common
	extern	__lneg
	extern	__lremu
