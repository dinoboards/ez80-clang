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
; bpopcnt - count the number of bits set in the 8-bit value in register A
;--------------------------------------------------------------
	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__bpopcnt
__bpopcnt:
	push	hl
	ld	l, a
	ld	h, 0

	; Multiplying HL by 2 increases H by H+(L>>7).
	; Use A to track these values of H to cancel from each iteration.
	; On the first iteration H is 0, so skip subtracting it.
	add	hl, hl
	sub	a, h
	add	hl, hl
	sub	a, h
	add	hl, hl
	sub	a, h
	add	hl, hl
	sub	a, h
	add	hl, hl
	sub	a, h
	add	hl, hl
	sub	a, h
	add	hl, hl
	sub	a, h
	; Note that the value of H after the 8th shift would be equivalent to the
	; initial value of A, so instead of shifting and adding H to A at the end,
	; simply offset from the initial value of A from the beginning.

	pop	hl
	ret
