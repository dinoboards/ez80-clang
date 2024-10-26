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
