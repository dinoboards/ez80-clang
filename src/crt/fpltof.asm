;--------------------------------------------------------------
;
;			Code Generation Helper
;		    For the Zilog eZ80 C Compiler
;	        Copyright 1992-2008 Zilog, Inc.
;
;--------------------------------------------------------------
;--------------------------------------------------------------
;
;	  	Signed long to IEEE Single precision.
;
; INPUTS:	AuBC 32-bit	signed long.
;
; OUTPUTS:	AuBC 32-bit	IEEE Single precision.
;
;--------------------------------------------------------------

	.assume adl=1

	section	.text,"ax",@progbits
	.global	__ltof, __ltod

__ltof:
__ltod:
	push	de
	ld	de,7Fh+23
	or	a,a
	jp	p,plus

	push	hl
	ld	hl,0
	sbc	hl,bc
	push	hl
	pop	bc
	pop	hl
	ld	d,a
	ld	a,0
	sbc	a,d
	jp	p,notmin	;skip if now positive

	srl	a		;was/is 80000000H, adjust mantissa = 40000000H
	inc	e		;adjust exponent
notmin:
	ld	d,1		; sign bit
plus:
	call	__fppack
	pop	de
	ret

	extern	__fppack
