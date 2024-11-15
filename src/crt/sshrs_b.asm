; (c) Copyright 2001-2008 Zilog, Inc.
;-------------------------------------------------------------------------
; Short Shift Right Signed
; Input:
;	Operand1:
;		  A  : 8 bit number of bits to shift
;	Operand2:
;		  HL : 16 bit value to be shifted by C
;
; Output:
;	Result:   HL : 16 bit
; Registers Used:
;	none
;-------------------------------------------------------------------------
	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__sshrs_b

__sshrs_b:
	push	bc
	ld	c, a
	call	__sshrs
	pop	bc
	ret

	extern	__sshrs


