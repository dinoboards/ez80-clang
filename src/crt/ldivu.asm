	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__ldivu

__ldivu:
; I: EUHL=dividend, AUBC=divisor
; O: euhl=EUHL/AUBC

	push	bc

	call	__ldvrmu

	ld	a, b
	pop	bc

	ret	z
	ei
	ret

	extern	__ldvrmu
