	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__lcmps

__lcmps:
	push	de
	ld	d, a
	ld	a, e
	sub	a, d
	jr	nz, .finish
	sbc	hl, bc
	add	hl, bc
	sbc	a, a
.finish:
	ld	a, d
	pop	de
	ret

