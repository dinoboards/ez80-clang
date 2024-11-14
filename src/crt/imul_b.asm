; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Integer Multiplication Signed/Unsigned.
;	Note:	When multipying two n-bit values, the low-order n-bits
;		of the product are the same, whether or not the values
;		are considered signed or unsigned.
; Input:
;	Operand1:
;		  uHL : 24 bits
;
;	Operand2:
;		  A : 8 bits
;
; Output:
;	Result:   uHL : 24 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__imul_b

__imul_b:
	push	bc
	ld	bc, 0
	ld	c, a
	call	__imulu
	pop	bc
	ret

	extern	__imulu
