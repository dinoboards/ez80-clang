	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__lsub

__lsub:
	push	af
	or	a, a
	sbc	hl, bc
	cpl
	ccf
	adc	a, e
	ld	e, a
	pop	af
	ret

