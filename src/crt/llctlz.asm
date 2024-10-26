	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__llctlz
__llctlz:
	push	bc
	push	de
	push	hl

	scf
	sbc	a, a

.loop:
	adc	hl, hl
	ex	de, hl
	adc	hl, hl
	ex	de, hl
	rl	c
	rl	b
	inc	a
	jr	nc, .loop

	pop	hl
	pop	de
	pop	bc
	ret
