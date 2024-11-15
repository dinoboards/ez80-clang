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
	.global	_ldiv
_ldiv:

	pop	hl
	pop	iy
	pop	de
	pop	bc
	ld	a, c
	pop	bc
	ex	(sp), hl
	ex	de, hl

	ld	d, a
	xor	a, e
	push	af

	ld	a, e
	ld	e, d
	push	de

	bit	7, e
	call	__ldivs_lrems_common

	call	__ldvrmu

	exx
	ld	e, a
	pop	af
	call	m, __lneg
	ld	(iy+4), hl
	ld	(iy+7), e

	exx
	pop	af
	call	m, __lneg
	ld	(iy), hl
	ld	(iy+3), e

	ex	(sp), hl
	push	de
	push	de
	push	de
	push	de
	bit	2, c
	jr	z, .ei_skip
	ei
.ei_skip:
	jp	(hl)


	extern	__ldivs_lrems_common
	extern	__ldvrmu
	extern	__lneg
