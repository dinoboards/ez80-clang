	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__indcallhl
__indcallhl:
	jp	(hl)
