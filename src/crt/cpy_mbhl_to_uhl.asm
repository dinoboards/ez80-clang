	.assume	adl=1

	section	.text, "ax", @progbits
	.global	ez80_cpy_mbhl_to_uhl

ez80_cpy_mbhl_to_uhl:
	push	ix
	push	af
	ld	ix, 0
	add	ix, sp
	push	hl
	ld	a, MB
	ld	(IX-1), a
	pop	hl
	pop	af
	pop	ix
	ret
