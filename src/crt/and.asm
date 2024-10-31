	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__land

LD_A_N = 0x3E

__land:
; CC: 28*r(PC)+11*r(SPL)+10*w(SPL)+1
	push	af
	and	a, e
	ld	e, a

	db	LD_A_N	; push af -> ld a,*

	.global	__iand
__iand:
; CC: 24*r(PC)+11*r(SPL)+10*w(SPL)+1
	push	af
	.local	__iand.hijack_land
.hijack_land:
	push	hl
	scf
	sbc	hl, hl
	add	hl, sp
	push	bc
	ld	a, (hl)
	inc	hl
	ld	sp, hl
	inc	hl
	inc	hl
	and	a, (hl)
	ld	(hl), a
	pop	hl
	ld	a, h
	and	a, b
	ld	h, a
	ld	a, l
	and	a, c
	ld	l, a
	pop	af
	ret

