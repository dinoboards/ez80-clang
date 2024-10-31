	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__lneg

__lneg:
	push	af
	push	de
	ex	de, hl	; ude=UHL, l=E
	xor	a, a	; a=0
	sbc	hl, hl	; uhl=0
	sbc	hl, de	; uhl=-UHL
	pop	de	; e=E
	sbc	a, e
	ld	e, a	; euhl=-EUHL
	pop	af
	ret
