; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Unsigned Short to Integer Conversion
; Input:
;	Operand1:
;                 BC : 16 bit number to convert
;
; Output:
;       Result:   HL : 24 bit
; Registers Used:
;	a
;-------------------------------------------------------------------------

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__stoiu
__stoiu:
	or	a, a
	sbc	hl, hl
	ld	l, c
	ld	h, b
	ret
