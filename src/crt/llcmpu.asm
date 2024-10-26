	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__llcmpu
__llcmpu:
	push	iy
	ld	iy, 0
	add	iy, sp
	push	hl
	ld	hl, (iy + 12)
	sbc.s	hl, bc
	jr	nz, .ne
	ld	hl, (iy + 9)
	sbc	hl, de
	jr	nz, .ne
	pop	hl
	push	bc
	ld	bc, (iy + 6)
	sbc	hl, bc
	add	hl, bc
	pop	bc
	pop	iy
	ret

.ne:
	ccf
	pop	hl
	pop	iy
	ret
