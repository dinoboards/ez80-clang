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
; This function adds an 8 bit number to a 24-bit number together
; Arguments: HL = 24-bit number, A = 8-bit number
; Returns: HL = HL + A
;--------------------------------------------------------------
	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__ladd_b

__ladd_b:
	push	bc
	inc.s	bc
	ld	c, a
	ld	b, 0
	add	hl, bc
	pop	bc
	ret	nc
	inc	e
	ret
