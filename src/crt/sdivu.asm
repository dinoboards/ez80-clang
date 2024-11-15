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
	.global	__sdivu

__sdivu:
; I: HL=dividend, BC=divisor
; O: uhl=HL/BC

	push	de

	call	__sdvrmu
	ex	de, hl

	pop	de
	ret

	extern	__sdvrmu
