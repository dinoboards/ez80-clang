;--------------------------------------------------------------
;
;			Code Generation Helper
;		    For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc.
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Single precision sub
; Input:
;	Operand1:
;		  abc : 32 bit IEEE single precision
;
;	Operand2:
;		  ehl : 32 bit IEEE single precision
;
; Output:
;	Result:   abc : 32 bit IEEE single precision (abc - ehl)
; Registers Used:

;-------------------------------------------------------------------------

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__fsub
__fsub:
	push	af
	ld	a, e
	xor	a, 80h	 	;Change op2 sign.
	ld	e, a
	pop	af
	call	__fadd		;Add the two.
	push	af
	ld	a, e
	xor	a, 80h	 	;restore op2 sign.
	ld	e, a
	pop	af
	ret

	extern	__fadd
