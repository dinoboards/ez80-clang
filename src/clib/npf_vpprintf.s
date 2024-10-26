	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_npf_vpprintf
_npf_vpprintf:
	push	ix
	ld	ix, 0
	add	ix, sp
	lea	hl, ix - 71
	ld	sp, hl
	ld	de, (ix + 9)
	ld	hl, (ix + 12)
	ld	(ix - 53), hl
	ld	hl, (ix + 15)
	ld	(ix - 62), hl
	ld	bc, 0
	lea	hl, ix - 18
	ld	(ix - 56), hl
	lea	hl, ix - 50
	ld	(ix - 59), hl
	ld	hl, (ix + 6)
	ld	(ix - 18), hl
	ld	(ix - 15), de
	ld	(ix - 12), bc
BB0_1:
	ld	hl, (ix - 53)
	ld	e, (hl)
	ld	a, e
	rlc	a
	sbc	hl, hl
	ld	a, e
	or	a, a
	jp	z, BB0_65
	ld	a, e
	cp	a, 37
	jr	nz, BB0_5
	pea	ix - 9
	ld	hl, (ix - 53)
	push	hl
	call	_npf_parse_format_spec
	push	hl
	pop	de
	ld	hl, 6
	add	hl, sp
	ld	sp, hl
	push	de
	pop	hl
	add	hl, bc
	or	a, a
	sbc	hl, bc
	jr	nz, BB0_7
	ld	hl, (ix - 53)
	ld	a, (hl)
	ld	l, a
	rlc	l
	sbc	hl, hl
	ld	l, a
	jr	BB0_6
BB0_5:
	ld	l, e
BB0_6:
	ld	de, (ix - 56)
	ld	bc, (ix - 53)
	inc	bc
	ld	(ix - 53), bc
	push	de
	push	hl
	call	_npf_putc_cnt
	ld	hl, 6
	add	hl, sp
	ld	sp, hl
	jr	BB0_1
BB0_7:
	ld	hl, (ix - 53)
	add	hl, de
	ld	(ix - 53), hl
	ld	de, (ix - 4)
	push	de
	pop	hl
	ld	bc, 8
	or	a, a
	sbc	hl, bc
	jr	nc, BB0_1
	ld	hl, JTI0_0
	add	hl, de
	add	hl, de
	add	hl, de
	ld	hl, (hl)
	jp	(hl)
BB0_9:
	ld	(ix - 50), 37
	ld	hl, (ix - 59)
	ld	(ix - 65), hl
	ld	bc, 1
	jp	BB0_64
BB0_10:
	ld	de, (ix - 62)
	push	de
	pop	iy
	lea	bc, iy + 3
	ex	de, hl
	ld	a, (hl)
	ld	(ix - 50), a
	ld	(ix - 62), bc
	ld	bc, 1
	jp	BB0_51
BB0_11:
	ld	hl, (ix - 62)
	push	hl
	pop	iy
	lea	bc, iy + 3
	ld	hl, (hl)
	ld	(ix - 65), hl
	ld	a, (hl)
	or	a, a
	jp	nz, BB0_19
	ld	(ix - 62), bc
	ld	bc, 0
	xor	a, a
	jp	BB0_52
BB0_13:
	ld	de, (ix - 7)
	push	de
	pop	hl
	ld	bc, 4
	or	a, a
	sbc	hl, bc
	jp	c, BB0_22
	ld	a, (ix - 9)
	ld	(ix - 68), a
	ld	iy, 0
	xor	a, a
	ld	e, a
	ld	bc, (ix - 59)
	jp	BB0_35
BB0_15:
	ld	hl, (ix - 7)
	push	hl
	pop	iy
	ld	bc, 4
	or	a, a
	sbc	hl, bc
	jp	c, BB0_24
	or	a, a
	sbc	hl, hl
	ld	(ix - 65), hl
	xor	a, a
	ld	l, a
	ld	(ix - 68), hl
	jp	BB0_42
BB0_17:
	ld	iy, (ix - 62)
	lea	hl, iy + 3
	ld	(ix - 65), hl
	ld	hl, (iy)
	ld	de, 32
	push	de
	ld	de, 16
	push	de
	ld	de, 0
	push	de
	push	hl
	ld	hl, (ix - 59)
	push	hl
	call	_npf_utoa_rev
	push	hl
	pop	de
	ld	hl, 15
	add	hl, sp
	ld	sp, hl
	ld	hl, (ix - 65)
	ld	(ix - 62), hl
	ld	hl, 120
	ld	(ix - 71), hl
BB0_18:
	ld	(ix - 68), de
	ld	hl, (ix - 56)
	push	hl
	ld	hl, 48
	push	hl
	call	_npf_putc_cnt
	ld	hl, 6
	add	hl, sp
	ld	sp, hl
	ld	hl, (ix - 56)
	push	hl
	ld	hl, (ix - 71)
	push	hl
	call	_npf_putc_cnt
	ld	hl, 6
	add	hl, sp
	ld	sp, hl
	ld	bc, (ix - 68)
	jp	BB0_51
BB0_19:
	ld	de, 1
BB0_20:
	ld	hl, (ix - 65)
	add	hl, de
	inc	de
	ld	a, (hl)
	or	a, a
	jr	nz, BB0_20
	dec	de
	ld	(ix - 62), bc
	push	de
	pop	bc
	xor	a, a
	jp	BB0_52
BB0_22:
	ld	hl, JTI0_2
	add	hl, de
	add	hl, de
	add	hl, de
	ld	hl, (hl)
	jp	(hl)
BB0_23:
	ld	iy, (ix - 62)
	lea	bc, iy + 3
	ld	hl, (iy)
	jr	BB0_28
BB0_24:
	ld	hl, JTI0_1
	lea	bc, iy + 0
	add	hl, bc
	add	hl, bc
	add	hl, bc
	ld	hl, (hl)
	jp	(hl)
BB0_25:
	ld	iy, (ix - 62)
	lea	hl, iy + 3
	ld	bc, (iy)
	ld	(ix - 65), bc
	ld	c, 0
	jp	BB0_40
BB0_26:
	ld	iy, (ix - 62)
	lea	bc, iy + 3
	ld	de, (iy)
	ld	a, d
	ld	l, a
	rlc	l
	sbc	hl, hl
	ld	h, a
	ld	l, e
	jr	BB0_28
BB0_27:
	ld	iy, (ix - 62)
	lea	bc, iy + 3
	ld	a, (iy)
	ld	l, a
	rlc	l
	sbc	hl, hl
	ld	l, a
BB0_28:
	push	hl
	pop	iy
	add	iy, iy
	push	hl
	pop	iy
	sbc	hl, hl
	push	hl
	pop	de
	ld	(ix - 62), bc
	jr	BB0_30
BB0_29:
	ld	iy, (ix - 62)
	lea	hl, iy + 6
	ld	bc, (iy)
	ld	e, (iy + 3)
	push	bc
	pop	iy
	ld	(ix - 62), hl
BB0_30:
	ld	bc, (ix - 59)
	lea	hl, iy + 0
	call	__lcmpzero
	ld	a, 1
	jp	m, BB0_32
	ld	a, 0
BB0_32:
	bit	0, a
	ld	a, 45
	jr	nz, BB0_34
	ld	a, (ix - 9)
BB0_34:
	ld	(ix - 68), a
BB0_35:
	push	de
	push	iy
	push	bc
	call	_npf_itoa_rev
	push	hl
	pop	bc
	ld	hl, 9
	add	hl, sp
	ld	sp, hl
	ld	hl, (ix - 59)
	ld	(ix - 65), hl
	ld	a, (ix - 68)
	jp	BB0_52
BB0_36:
	ld	iy, (ix - 62)
	lea	hl, iy + 3
	ld	(ix - 71), hl
	ld	hl, (iy)
	ld	bc, 65535
	jr	BB0_38
BB0_37:
	ld	iy, (ix - 62)
	lea	hl, iy + 3
	ld	(ix - 71), hl
	ld	hl, (iy)
	ld	bc, 255
BB0_38:
	call	__iand
	ld	(ix - 65), hl
	ld	l, 0
	ld	(ix - 68), hl
	ld	hl, (ix - 71)
	jr	BB0_41
BB0_39:
	ld	iy, (ix - 62)
	lea	hl, iy + 6
	ld	bc, (iy)
	ld	(ix - 65), bc
	ld	c, (iy + 3)
BB0_40:
	ld	(ix - 68), bc
BB0_41:
	ld	(ix - 62), hl
BB0_42:
	ld	iy, (ix - 59)
	push	de
	pop	hl
	ld	bc, 5
	or	a, a
	sbc	hl, bc
	ld	bc, 16
	jr	z, BB0_44
	ld	bc, 10
BB0_44:
	ex	de, hl
	ld	de, 4
	or	a, a
	sbc	hl, de
	ld	de, 8
	jr	z, BB0_46
	push	bc
	pop	de
BB0_46:
	ld	a, (ix - 1)
	ld	l, a
	rlc	l
	sbc	hl, hl
	ld	l, a
	push	hl
	push	de
	ld	hl, (ix - 68)
	push	hl
	ld	hl, (ix - 65)
	push	hl
	push	iy
	call	_npf_utoa_rev
	push	hl
	pop	bc
	ld	hl, 15
	add	hl, sp
	ld	sp, hl
	ld	hl, (ix - 65)
	ld	de, (ix - 68)
	call	__lcmpzero
	jr	z, BB0_51
	ld	l, (ix - 8)
	ld	de, (ix - 4)
	ld	a, l
	or	a, a
	jr	z, BB0_50
	ld	a, l
	push	de
	pop	hl
	push	bc
	pop	iy
	ld	bc, 4
	or	a, a
	sbc	hl, bc
	ld	l, a
	lea	bc, iy + 0
	jr	nz, BB0_50
	ld	de, (ix - 59)
	push	de
	pop	hl
	add	hl, bc
	inc	bc
	ld	(hl), 48
	ld	(ix - 65), de
	jr	BB0_59
BB0_50:
	ld	a, l
	or	a, a
	jp	nz, BB0_60
BB0_51:
	xor	a, a
	ld	hl, (ix - 59)
	ld	(ix - 65), hl
BB0_52:
	ld	de, (ix - 4)
BB0_53:
	ex	de, hl
	ld	de, 2
	or	a, a
	sbc	hl, de
	jr	nz, BB0_57
	push	bc
	pop	hl
	ld	de, -8388608
	add	hl, de
	inc	de
	or	a, a
	sbc	hl, de
	jp	c, BB0_1
	ld	iy, (ix - 65)
BB0_56:
	ld	(ix - 68), bc
	ld	(ix - 65), iy
	ld	a, (iy)
	ld	l, a
	rlc	l
	sbc	hl, hl
	ld	l, a
	ld	de, (ix - 56)
	push	de
	push	hl
	call	_npf_putc_cnt
	ld	bc, (ix - 68)
	ld	iy, (ix - 65)
	ld	hl, 6
	add	hl, sp
	ld	sp, hl
	dec	bc
	inc	iy
	push	bc
	pop	hl
	add	hl, bc
	or	a, a
	sbc	hl, bc
	jr	nz, BB0_56
	jp	BB0_1
BB0_57:
	ld	e, a
	or	a, a
	jr	z, BB0_59
	ld	a, e
	rlc	a
	sbc	hl, hl
	ld	l, e
	ld	de, (ix - 56)
	push	de
	push	hl
	ld	(ix - 68), bc
	call	_npf_putc_cnt
	ld	bc, (ix - 68)
	ld	hl, 6
	add	hl, sp
	ld	sp, hl
BB0_59:
	push	bc
	pop	hl
	ld	de, -8388608
	add	hl, de
	inc	de
	jr	BB0_63
BB0_60:
	ld	(ix - 68), bc
	push	de
	pop	hl
	ld	bc, 5
	or	a, a
	sbc	hl, bc
	jr	nz, BB0_62
	ld	a, (ix - 1)
	ld	l, a
	rlc	l
	sbc	hl, hl
	ld	l, a
	ld	de, 88
	add	hl, de
	ld	(ix - 71), hl
	add	hl, bc
	or	a, a
	sbc	hl, bc
	ld	de, (ix - 68)
	push	de
	pop	bc
	ld	hl, (ix - 59)
	ld	(ix - 65), hl
	jp	nz, BB0_18
	jr	BB0_59
BB0_62:
	ld	bc, (ix - 68)
	xor	a, a
	ld	hl, (ix - 59)
	ld	(ix - 65), hl
	jp	BB0_53
BB0_63:
	or	a, a
	sbc	hl, de
	jp	c, BB0_1
BB0_64:
	ld	iy, (ix - 65)
	add	iy, bc
	dec	bc
	ld	(ix - 68), bc
	ld	a, (iy - 1)
	ld	l, a
	rlc	l
	sbc	hl, hl
	ld	l, a
	ld	de, (ix - 56)
	push	de
	push	hl
	call	_npf_putc_cnt
	ld	bc, (ix - 68)
	ld	hl, 6
	add	hl, sp
	ld	sp, hl
	push	bc
	pop	de
	inc	de
	ex	de, hl
	ld	de, 2
	jr	BB0_63
BB0_65:
	ld	hl, (ix - 12)
	ld	sp, ix
	pop	ix
	ret
	section	.text,"ax",@progbits
	section	.rodata,"a",@progbits
	.local	JTI0_0
JTI0_0:
	d24	BB0_9
	d24	BB0_10
	d24	BB0_11
	d24	BB0_13
	d24	BB0_15
	d24	BB0_15
	d24	BB0_15
	d24	BB0_17
	.local	JTI0_1
JTI0_1:
	d24	BB0_25
	d24	BB0_36
	d24	BB0_37
	d24	BB0_39
	.local	JTI0_2
JTI0_2:
	d24	BB0_23
	d24	BB0_26
	d24	BB0_27
	d24	BB0_29

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__Unwind_SjLj_Register
	.extern	__lcmpzero
	.extern	_npf_itoa_rev
	.extern	_npf_parse_format_spec
	.extern	__Unwind_SjLj_Unregister
	.extern	__iand
	.extern	_npf_putc_cnt
	.extern	_npf_utoa_rev
