	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_memset
_memset:
	pop	iy
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	push	iy
	cpi
	add	hl,bc
	ret	c
	dec	hl
	ld	(hl),e
	ret	po
	push	hl
	pop	de
	dec	de
	lddr
	ret
