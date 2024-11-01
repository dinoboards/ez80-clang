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
	.global	__ldivs_lrems_common

__ldivs_lrems_common:
; I: ZF=EUHL>=0
; O: aubc=abs(AUBC), euhl=abs(EUHL)

	call	nz, __lneg

	or	a, a
	ret	p

	push	hl
	sbc	hl, hl
	sbc	hl, bc
	ex	(sp), hl
	pop	bc
	cpl
	sbc	a, -1

	ret

	extern	__lneg
