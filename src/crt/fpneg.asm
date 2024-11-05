;--------------------------------------------------------------
;
;	        Code Generation Helper
;		For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc.
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	IEEE Negate.
;
; INPUTS:
;		AuBC:	32-bit IEEE Single Precision.
;
; OUTPUTS:
;		AuBC:	32-bit IEEE Single Precision.
;
;--------------------------------------------------------------
	.assume adl=1

	section	.text,"ax",@progbits
	.global	__fneg
__fneg:
	or	a,a
	jr	nz,__noexit
	push	hl
	sbc	hl,hl
	sbc	hl,bc
	pop	hl
	ret	z
__noexit:
	xor	a,80h
	ret
