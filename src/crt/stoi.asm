; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Signed Short to Integer Conversion
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
	.global	__stoi
__stoi:
	ld	h, b
	sla	h
	sbc	hl, hl
	ld	l, c
	ld	h, b
	ret
