; (c) Copyright 2007-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Byte Shift Right Signed
; Input:
;	Operand1:
;                 A : 8 bit number to shift
;	Operand2:
;                 B : 8 bit shift count
;
; Output:
;       Result:   A : 8 bit
; Registers Used:
;       flags
;-------------------------------------------------------------------------
	.global	__bshrs
	section	.text, "ax", @progbits
	.assume	adl=1

__bshrs:
	push	bc
	inc	b
	jr	test

loop:
	sra	a
test:
	djnz	loop

	pop	bc
	ret

