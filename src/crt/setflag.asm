; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Set Sign flag for signed comparison
;	s <-- s xor v
; Input:
;	Operand1: f register
;
; Output:
;	Result:  updated f register
;
; Registers Used:
;	None
;-------------------------------------------------------------------------
;	if ( V == 0)
;		S = S xor 0 -> S = S
;	if ( V != 0)
;		S = S xor V

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__setflag
__setflag:

	push	bc

	push	af
	pop	bc		; c <- flags

	bit	2, c		; if (v == 1)
	jr	z, _done		; else go to .done
	ld	a, c		; c <- c xor %80
	xor	a, 80h
	ld	c, a

_done:
	push	bc
	pop	af		; flags <- c
	pop	bc
	ret

