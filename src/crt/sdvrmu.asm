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
	.global	__sdvrmu

__sdvrmu:
; I: HL=dividend, BC=divisor
; O: a=0, ude=HL/BC, uhl=HL%BC

	push	hl
	dec	sp
	pop	de
	inc	sp
	ld	e, 0

	inc	bc
	dec.s	bc

	push	af
	ld	a, 16

	jp	__idvrmu_hijack_a_iters_ude_dividend

	extern	__idvrmu_hijack_a_iters_ude_dividend
