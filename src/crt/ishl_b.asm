; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer Shift Left
; Input:
;	Operand1: 
;		  A : 8 bit number of bits to shift
;	Operand2: 
;		  HL : 24 bit value to be shifted by C
;
; Output:
;	Result:   HL : 24 bit 
; Registers Used:
;	none
;-------------------------------------------------------------------------

	.assume	adl=1

	section	.text,"ax",@progbits

	.global	__ishl_b
__ishl_b:
	push bc
	ld c,a
	call __ishl
	pop bc
	ret

	extern	__ishl