	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__lcmpzero
__lcmpzero:
	inc	e
	dec	e
	ret	nz
	add	hl, bc
	or	a, a
	sbc	hl, bc
	ret	p
	inc	e
	dec	de
	ret
