	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__ladd

__ladd:
	push	af
	add	hl, bc
	adc	a, e
	ld	e, a
	pop	af
	ret
