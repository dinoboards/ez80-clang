; (c) Copyright 2001-2008 Zilog, Inc.

; Input:
;	EuHL = dividend
;	AuBC = divisor
; Output:
;	EuIX = quotient
;	AuHL = remainder

	.assume	adl=1
	.global	__ldvrmu
	section	.text, "ax", @progbits

__ldvrmu:
	push	hl
	pop	ix
	ld	iyh, a
	ld	iyl, 32
	xor	a, a
	sbc	hl, hl
_loop:
	add	ix, ix		;shift AuHLEuIX left
	rl	e
	adc	hl, hl
	rla
	sbc	hl, bc
	sbc	a, iyh
	jr	nc, _L1
	add	hl, bc
	adc	a, iyh
	jr	_L2
_L1:
	inc	ix
_L2:
	dec	iyl
	jr	nz, _loop
	ret
