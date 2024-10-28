	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__sand

__sand:
	push	af
	ld	a, h
	and	a, b
	ld	h, a
	ld	a, l
	and	a, c
	ld	l, a
	pop	af
	ret
