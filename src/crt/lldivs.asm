	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__llrems
__llrems:

JR_NC_OP_CODE = 0x30

	scf
; virtual
; 	jr	nc, $ + 2
; 	load .jr_nc: 1 from $$
; end virtual
	db	JR_NC_OP_CODE ; as CF is always set, we never JP - but the or a,a is ignored - i guess

	.global	__lldivs
__lldivs:

	or	a, a

	push	iy
	push	af

	ld	iy, 2
	add	iy, sp

	ld	a, b
	ld	(iy), a
	xor	a, (iy + 14)
	ld	(iy + 15), a

	xor	a, b
	rla
	jr	nc, .neg_divisor_skip

	push	bc
	push	hl

	lea	hl, iy + 7
	xor	a, a
	ld	c, a
	ld	b, 8

.neg_divisor_loop:
	ld	a, c
	sbc	a, (hl)
	ld	(hl), a
	inc	hl
	djnz	.neg_divisor_loop

	pop	hl
	pop	bc
.neg_divisor_skip:

	bit	7, b
	call	nz, __llneg

	or	a, a
	call	__lldvrmu_hijack

	pop	af
	bit	7, (iy + 8)
	jr	c, .div_quotient_skip
	ld	hl, (iy + 15)
	ld	de, (iy + 18)
	ld	bc, (iy + 21)
	bit	7, (iy + 23)
.div_quotient_skip:

	call	nz, __llneg

	pop	iy

	ret

	extern	__lldvrmu_hijack
	extern	__llneg
