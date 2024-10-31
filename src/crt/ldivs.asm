	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__ldivs

__ldivs:
; I: EUHL=dividend, AUBC=divisor
; O: euhl=EUHL/AUBC

	bit	7, e
	push	af
	push	bc

	call	__ldivs_lrems_common

	call	__ldivu

	pop	bc
	pop	af

	rlca
	rrca
	jr	nz, .pos_dividend_skip
	ccf
.pos_dividend_skip:

	ret	c
	jp	__lneg

	extern	__ldivs_lrems_common
	extern	__ldivu
	extern	__lneg
