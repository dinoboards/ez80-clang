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
; This function adds two 24-bit numbers together
; Arguments: HL = 24-bit number, BC = 24-bit number
; Returns: HL = HL + BC
;--------------------------------------------------------------

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__ladd

__ladd:
	push	af
	add	hl, bc
	adc	a, e
	ld	e, a
	pop	af
	ret
