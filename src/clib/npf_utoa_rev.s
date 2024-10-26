	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_npf_utoa_rev
_npf_utoa_rev:
	push	ix
	ld	ix, 0
	add	ix, sp
	lea	hl, ix - 14
	ld	sp, hl
	ld	iy, (ix + 9)
	ld	a, (ix + 12)
	ld	bc, (ix + 15)
	ld	hl, (ix + 18)
	ld	(ix - 6), hl
	ld	de, 55
	sbc	hl, hl
	ld	(ix - 3), hl
	ld	hl, (ix - 6)
	add	hl, de
	ld	(ix - 6), hl
BB0_1:
	ld	hl, (ix + 6)
	ld	de, (ix - 3)
	add	hl, de
	ld	(ix - 14), hl
	lea	hl, iy + 0
	ld	(ix - 7), a
	ld	e, a
	xor	a, a
	call	__ldivu
	ld	(ix - 10), hl
	ld	(ix - 11), e
	call	__lmulu
	push	hl
	pop	de
	lea	bc, iy + 0
	lea	hl, iy + 0
	or	a, a
	sbc	hl, de
	push	hl
	pop	iy
	ld	de, 10
	or	a, a
	sbc	hl, de
	ld	hl, 48
	jr	c, BB0_3
	ld	hl, (ix - 6)
BB0_3:
	ld	a, l
	add	a, iyl
	ld	hl, (ix - 14)
	ld	(hl), a
	ld	hl, (ix - 3)
	inc	hl
	ld	(ix - 3), hl
	push	bc
	pop	hl
	ld	e, (ix - 7)
	ld	bc, (ix + 15)
	xor	a, a
	call	__lcmpu
	ld	iy, (ix - 10)
	ld	a, (ix - 11)
	jr	nc, BB0_1
	ld	hl, (ix - 3)
	ld	sp, ix
	pop	ix
	ret
	section	.text,"ax",@progbits

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__ldivu
	.extern	__Unwind_SjLj_Register
	.extern	__Unwind_SjLj_Unregister
	.extern	__lmulu
	.extern	__lcmpu
