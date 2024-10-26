	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_npf_itoa_rev
_npf_itoa_rev:
	push	ix
	ld	ix, 0
	add	ix, sp
	lea	hl, ix - 11
	ld	sp, hl
	ld	iy, (ix + 9)
	sbc	hl, hl
	ld	(ix - 3), hl
	ld	d, (ix + 12)
BB0_1:
	ld	hl, (ix + 9)
	ld	e, (ix + 12)
	call	__lcmpzero
	ld	a, 1
	jp	m, BB0_3
	ld	a, 0
BB0_3:
	ld	(ix - 11), a
	ld	hl, (ix + 6)
	ld	bc, (ix - 3)
	add	hl, bc
	ld	(ix - 10), hl
	lea	hl, iy + 0
	ld	e, d
	ld	bc, 10
	xor	a, a
	call	__ldivs
	ld	(ix - 6), hl
	ld	(ix - 7), e
	call	__lmulu
	push	hl
	pop	bc
	ld	a, e
	lea	hl, iy + 0
	ld	e, d
	call	__lsub
	push	hl
	pop	bc
	call	__lneg
	bit	0, (ix - 11)
	jr	nz, BB0_5
	push	bc
	pop	hl
BB0_5:
	ld	a, l
	add	a, 48
	ld	hl, (ix - 10)
	ld	(hl), a
	ld	hl, (ix - 3)
	inc	hl
	ld	(ix - 3), hl
	lea	hl, iy + 0
	ld	e, d
	ld	bc, 9
	xor	a, a
	call	__ladd
	ld	bc, 19
	call	__lcmpu
	ld	iy, (ix - 6)
	ld	d, (ix - 7)
	jr	nc, BB0_1
	ld	hl, (ix - 3)
	ld	sp, ix
	pop	ix
	ret
	section	.text,"ax",@progbits

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__ldivs
	.extern	__Unwind_SjLj_Register
	.extern	__Unwind_SjLj_Unregister
	.extern	__lcmpzero
	.extern	__lmulu
	.extern	__lsub
	.extern	__lcmpu
	.extern	__lneg
	.extern	__ladd
