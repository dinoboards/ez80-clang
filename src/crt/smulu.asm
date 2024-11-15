;--------------------------------------------------------------
;
;	C RUNTIME FUNCTION
;	For the eZ80 Clang cross compiler
;
;  Original file source: https://github.com/CE-Programming/toolchain
;  License: https://github.com/CE-Programming/toolchain?tab=LGPL-3.0-1-ov-file
;
; Modified to comply with GNU AS assembler (ez80-none-elf-as) syntax
;
;--------------------------------------------------------------
	.assume	adl=1

	section	.text, "ax", @progbits
	; .global	__smuls
	.global	__smulu

; __smuls:
__smulu:

; Multiplies HL by BC and returns the 16-bit product hl.
;    I: BC=multiplier, HL=multiplicand
;    O: hl=HL*BC, hlu=ADL&&(L*C+(H*C+L*B<<8&0xFFFF)>>16)
;   FO: c=!ADL&&(L*C+(H*C+L*B<<8&0xFFFF)>>16)
;   CC: 20*r(PC)+(ADL?6*r(SPL)+3*w(SPL):4*r(SPS)+2*w(SPS))+13
				; ude		uhl		u(sp)
Mul_HL_BC_HL:			;--------------+---------------+----------------
	push	de		;				u(sp)=UDE
	ld	d, h		;  d =H
	ld	e, c		;  de=HC
	mlt	de		; ude=H*C
	ld	d, l		;  d=L
	ld	h, b		;		 hl=BL
	mlt	hl		;		uhl=L*B
	add	hl, de		;		uhl=(L<<8)+(H*C&0xFF)+L*B
	ld	h, l
	ld	l, 0		;		uhl=H*C+L*B<<8&0xFFFF
	ld	e, c		; ude=LC
	mlt	de		; ude=L*C
	add	hl, de		;		uhl=L*C+(H*C+L*B<<8&0xFFFF)
	pop	de		; ude=UDE			------
	ret

; HL*BC&0xFFFF=L*C+(H*C+L*B<<8)+(H*B<<16)&0xFFFF
;	      =L*C+(H*C+L*B<<8)&0xFFFF
