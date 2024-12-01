	section	.text,"ax",@progbits
	.assume	adl = 1
	.global	_exp2f
_exp2f:
	call	__frameset0
	ld	hl, (ix + 6)
	ld	de, 0
	ld	c, (ix + 9)
	push	bc
	push	hl
	ld	hl, 64
	push	hl
	push	de
	call	_pow
	ld	sp, ix
	pop	ix
	ret

	.global	_exp2
.set _exp2, _exp2f

	.extern	__frameset0
	.extern	_pow
