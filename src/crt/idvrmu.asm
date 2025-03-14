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
; Performs 16-bit unsigned division
; Arguments: uhl = dividend, ubc = divisor
; Results: ude=UHL/UBC, uhl=UHL%UBC
;--------------------------------------------------------------

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__idvrmu

__idvrmu:
	ex	de, hl

	push	af
	ld	a, 24
	.global	__idvrmu_hijack_a_iters_ude_dividend
__idvrmu_hijack_a_iters_ude_dividend:

	or	a, a
	sbc	hl, hl

.loop:
	ex	de, hl
	add	hl, hl
	ex	de, hl
	adc	hl, hl

	sbc	hl, bc
	inc	e

	jr	nc, .restore_skip
	add	hl, bc
	dec	e
.restore_skip:

	dec	a
	jr	nz, .loop

	pop	af
	ret

