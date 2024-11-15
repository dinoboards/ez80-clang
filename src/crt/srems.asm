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
	.global	__srems

__srems:
; I: HL=dividend, BC=divisor
; O: uhl=HL%BC

	push	de

	call	__sdvrms_abs

	pop	de
	ret	nc

	jp	__ineg

	extern	__ineg
	extern	__sdvrms_abs

