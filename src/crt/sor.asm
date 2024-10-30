	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__sor

__sor:
	push	af
	ld	a, h
	or	a, b
	ld	h, a
	ld	a, l
	or	a, c
	ld	l, a
	pop	af
	ret
