; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Long Division Unsigned
; Input:
;	Operand1:
;		  EuHL : 32 bits
;
;	Operand2:
;		  AuBC : 32 bits
; Output:
;	Result:   EuHL : 32 bits
;
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume	adl=1
	.global	__ldivu
	section	.text, "ax", @progbits

__ldivu:
	push	ix
	push	iy
	call	__ldvrmu
	ld	a, iyh
	push	ix
	pop	hl
	pop	iy
	pop	ix
	ret

