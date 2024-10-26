	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__lcmpu

__lcmpu:
	cp	a, e
	ccf
	ret	nz
	or	a, a
	sbc	hl, bc
	add	hl, bc
	ret

