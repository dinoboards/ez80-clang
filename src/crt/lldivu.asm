	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__lldivu
__lldivu:

	push	iy
	push	af

	call	__lldvrmu

	ld	hl, (iy + 15)
	ld	de, (iy + 18)
	ld	bc, (iy + 21)

	pop	af
	pop	iy

	ret

	extern	__lldvrmu
