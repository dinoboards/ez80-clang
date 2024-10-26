	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_npf_parse_format_spec
_npf_parse_format_spec:
	push	ix
	ld	ix, 0
	add	ix, sp
	lea	hl, ix - 7
	ld	sp, hl
	ld	hl, (ix + 6)
	ld	iy, (ix + 9)
	ld	(iy + 8), 32
	ld	(iy), 0
	ld	(iy + 1), 0
	push	hl
	pop	de
	push	hl
	pop	iy
	inc	de
	ld	l, (iy + 1)
	ld	a, l
	ex	de, hl
	ld	iyl, e
	ex	de, hl
	rlc	a
	sbc	hl, hl
	push	hl
	pop	bc
	ex	de, hl
	ld	e, iyl
	ex	de, hl
	ld	a, l
	or	a, a
	jr	nz, BB0_2
	ld	hl, (ix + 6)
	ld	(ix - 3), hl
	jr	BB0_13
BB0_2:
	xor	a, a
	ld	(ix - 7), a
	ld	c, l
BB0_3:
	push	de
	pop	iy
	push	bc
	pop	hl
	ld	de, 32
	or	a, a
	sbc	hl, de
	jr	nz, BB0_6
	ld	a, (ix - 7)
	or	a, a
	jr	nz, BB0_11
	ld	hl, (ix + 9)
	ld	(hl), 32
	ld	d, 32
	jr	BB0_10
BB0_6:
	push	bc
	pop	hl
	ld	de, 35
	or	a, a
	sbc	hl, de
	jr	nz, BB0_8
	lea	hl, iy + 0
	ld	iy, (ix + 9)
	ld	(iy + 1), 35
	push	hl
	pop	iy
	jr	BB0_11
BB0_8:
	push	bc
	pop	hl
	ld	de, 43
	or	a, a
	sbc	hl, de
	jr	nz, BB0_12
	ld	hl, (ix + 9)
	ld	(hl), 43
	ld	d, 43
BB0_10:
	ld	(ix - 7), d
BB0_11:
	ld	(ix - 6), iy
	ld	de, (ix - 6)
	inc	de
	ld	iy, (ix - 6)
	ld	a, (iy + 1)
	ld	l, a
	rlc	l
	sbc	hl, hl
	push	hl
	pop	bc
	ld	c, a
	or	a, a
	ld	hl, (ix - 6)
	ld	(ix - 3), hl
	jr	nz, BB0_3
	jr	BB0_13
BB0_12:
	lea	hl, iy + 0
	dec	hl
	ld	(ix - 3), hl
	lea	de, iy + 0
BB0_13:
	ld	hl, (ix + 9)
	push	hl
	pop	iy
	or	a, a
	sbc	hl, hl
	ld	(iy + 2), hl
	ex	de, hl
	ld	iy, (ix - 3)
	lea	de, iy + 2
	ld	(ix - 6), de
	push	hl
	pop	iy
	ld	a, (iy)
	ld	l, a
	rlc	l
	sbc	hl, hl
	push	hl
	pop	de
	ld	e, a
	push	de
	pop	hl
	ld	bc, 104
	or	a, a
	sbc	hl, bc
	jr	nz, BB0_16
	ld	hl, 1
	ld	iy, (ix + 9)
	ld	(iy + 2), hl
	ld	iy, (ix - 3)
	ld	a, (iy + 2)
	cp	a, 104
	ld	iy, (ix - 6)
	jr	nz, BB0_18
	ld	iy, (ix + 9)
	ld	hl, 2
	ld	(iy + 2), hl
	ld	iy, (ix - 3)
	lea	iy, iy + 3
	jr	BB0_18
BB0_16:
	ld	bc, (ix - 6)
	ex	de, hl
	ld	de, 108
	or	a, a
	sbc	hl, de
	jr	nz, BB0_18
	ld	iy, (ix + 9)
	ld	hl, 3
	ld	(iy + 2), hl
	push	bc
	pop	iy
BB0_18:
	ld	a, (iy)
	ld	l, a
	rlc	l
	sbc	hl, hl
	ld	l, a
	ld	de, -37
	add	hl, de
	push	hl
	pop	de
	ld	bc, 84
	or	a, a
	sbc	hl, bc
	jr	c, BB0_21
	or	a, a
	sbc	hl, hl
BB0_20:
	ld	sp, ix
	pop	ix
	ret
BB0_21:
	lea	bc, iy + 0
	ld	hl, JTI0_0
	add	hl, de
	add	hl, de
	add	hl, de
	ld	iy, (hl)
	or	a, a
	sbc	hl, hl
	jp	(iy)
BB0_22:
	ld	iy, (ix + 9)
	ld	(iy + 8), 0
BB0_23:
	ld	hl, 5
	jr	BB0_30
BB0_24:
	ld	hl, 1
	jr	BB0_30
BB0_25:
	ld	hl, 3
	jr	BB0_30
BB0_26:
	ld	hl, 4
	jr	BB0_30
BB0_27:
	ld	hl, 7
	jr	BB0_30
BB0_28:
	ld	hl, 2
	jr	BB0_30
BB0_29:
	ld	hl, 6
BB0_30:
	inc	bc
	ld	iy, (ix + 9)
	ld	(iy + 5), hl
	ld	de, (ix + 6)
	push	bc
	pop	hl
	or	a, a
	sbc	hl, de
	ld	sp, ix
	pop	ix
	ret
	section	.text,"ax",@progbits
	section	.rodata,"a",@progbits
	.local	JTI0_0
JTI0_0:
	d24	BB0_30
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_22
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_24
	d24	BB0_25
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_25
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_20
	d24	BB0_26
	d24	BB0_27
	d24	BB0_20
	d24	BB0_20
	d24	BB0_28
	d24	BB0_20
	d24	BB0_29
	d24	BB0_20
	d24	BB0_20
	d24	BB0_23

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__Unwind_SjLj_Register
	.extern	__Unwind_SjLj_Unregister
