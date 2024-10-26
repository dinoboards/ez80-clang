	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__llremu
__llremu:

	push	iy
	push	af

	call	__lldvrmu

	pop	af
	pop	iy

	ret

	extern	__lldvrmu
