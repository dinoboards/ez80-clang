	.assume adl=1

	section	.text,"ax",@progbits
	.global	__frameset0

__frameset0:
	pop	hl
	push	ix
	ld	ix,0
	add	ix,sp
	jp	(hl)
