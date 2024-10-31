	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__lctlz
__lctlz:
	push	de
	push	hl

	scf
	sbc	a, a

.loop:
	adc	hl, hl
	rl	e
	inc	a
	jr	nc, .loop

	pop	hl
	pop	de
	ret
