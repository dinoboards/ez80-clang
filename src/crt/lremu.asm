	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__lremu

__lremu:
; I: EUHL=dividend, AUBC=divisor
; O: euhl=EUHL%AUBC

	call	__ldvrmu
	ld	e, a
	push	de
	exx
	ld	a, e
	pop	de

	ret	z
	ei
	ret

	extern	__ldvrmu
