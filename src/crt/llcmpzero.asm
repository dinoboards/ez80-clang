	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__llcmpzero
__llcmpzero:
	inc	b
	dec	b
	ret	nz
	inc.s	bc
	dec	c
	jr	nz, .p_nz
	or	a, a
	sbc	hl, bc
	jr	nz, .p_nz
	sbc	hl, de
	ret	z
	add	hl, de
.p_nz:
	inc	b
	ld	b, 0
	ret
