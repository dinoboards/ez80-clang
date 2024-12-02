; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Indirect Call
; Input:
;	Operand1:
;                 iy : 24 bit
;
; Output:
; Registers Used:
;-------------------------------------------------------------------------
	.assume	adl=1
	.global	__indcall
	section	.text, "ax", @progbits
__indcall:
	jp	(iy)

