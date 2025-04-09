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
; This function adds two 32-bit numbers together
; Arguments: EUHL = 32-bit number, AUBC = 32-bit number
; Returns: EUHL = EUHL + AUBC
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
