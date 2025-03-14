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
	.global	__idvrms

__idvrms:
; I: UHL=dividend, UBC=divisor
; O: ude=UHL%UBC, uhl=UHL/UBC

	push	bc
	push	af

	ex	de, hl

	sbc	hl, hl
	ccf
	sbc	hl, bc
	inc	hl
	jp	m, .neg_divisor_skip
	cpl
	push	hl
	pop	bc
.neg_divisor_skip:

	sbc	hl, hl
	ccf
	sbc	hl, de
	inc	hl
	jp	p, .pos_dividend_skip
	cpl
	ex	de, hl
.pos_dividend_skip:

	call	__idvrmu

	call	p, __ineg

	ld	b, a
	pop	af
	cp	a, b
	pop	bc
	ex	de, hl
	ret	nz
	jp	__ineg

	extern	__idvrmu
	extern	__ineg
