; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Signed Integer to Long conversion
; Input:
;	Operand1:
;                 BC : 24 bit
;
; Output:
;       Result:   A:BC : 32 bit
; Registers Used:
;
;-------------------------------------------------------------------------
	.assume	adl=1

	.global	__itol
	section	.text, "ax", @progbits
__itol:
	dec	sp
	push	bc
	inc	sp
	pop	af
	rla
	sbc	a, a
	ret


