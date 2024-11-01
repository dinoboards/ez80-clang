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

	section	.text,"ax",@progbits
	.global	__lmuls, __lmulu

__lmuls:
__lmulu:

; Multiplies EUHL by AUBC and returns the 32-bit product euhl.
;    I: AUBC=multiplier, EUHL=multiplicand, ADL=1
;    O: euhl=EUHL*AUBC
;   FO: --
;   CC: 93*r(PC)+15*w(SPL)+15*r(SPL)+41
;				; a		ude		uhl		uix		u(sp)
Mul_EUHL_AUBC_EUHL:		;--------------+---------------+---------------+---------------+----------------------------------------
	push	af		;								u(sp)=AF
	push	de		;									u(sp)=UDE
	push	ix		;										u(sp)=UIX
	ld	d, c		;		 de=CE
	mlt	de		;		ude=E*C
	ld	d, a		;		 d =A
	ld	a, e		; a=E*C
	ld	e, l		; 		 de=AL
	ld	ixl, e		;						 ixl=L
	mlt	de		;		ude=L*A
	add	a, e		; a=E*C+L*A
	dec	sp
	push	bc
	inc	sp
	inc	sp
	push	hl
	inc	sp
	inc	sp		;											 (sp)=[BCU][HLU]
	ld	d, h		;		 d =H
	ld	ixh, d		;						 ix=HL
	pop	hl		;				 hl=[BCU][HLU]						--
	ld	e, h		;		 de=H[BCU]
	mlt	de		;		ude=H*BCU
	add	a, e		; a=E*C+H*BCU+L*A
	ld	d, b		;		 d =B
	ld	e, l		;		 de=B[HLU]
	mlt	de		;		ude=HLU*B
	add	a, e		; a=E*C+HLU*B+H*BCU+L*A
	ld	d, h		;		 d =BCU
	ld	e, ixl		;		 de=[BCU]L
	ld	h, c		;				 hl=C[HLU]
	mlt	de		;		ude=L*BCU
	mlt	hl		;				uhl=HLU*C
	add	hl, de		;				uhl=HLU*C+L*BCU
	ld	d, b		;		 d =B
	ld	e, ixh		;		 de=BH
	mlt	de		;		ude=H*B
	add	hl, de		;				uhl=HLU*C+H*B+L*BCU
	add	a, h		; a=(HLU*C+H*B+L*BCU>>8)+E*C+HLU*B+H*BCU+L*A
	ld	h, l		;				 h =HLU*C+H*B+L*BCU
	ld	l, 0		;				 hl=HLU*C+H*B+L*BCU<<8
	ld	d, b		;		 d =B
	ld	e, ixl		;		 de=BL
	mlt	de		;		ude=L*B
	add.s	hl, de		;				uhl=L*B+(HLU*C+H*B+L*BCU<<8)&0xFFFF
	adc	a, 0		; a=L*B+(HLU*C+H*B+L*BCU<<8)+(E*C+HLU*B+H*BCU+L*A<<16)>>16
	ld	d, ixh		;		 d =H
	ld	e, c		;		 de=HC
	mlt	de		;		ude=H*C
	add	hl, de		;				uhl=H*C+(L*B+(HLU*C+H*B+L*BCU<<8)&0xFFFF)
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl		;				uhl=(H*C+L*B<<8)+(HLU*C+H*B+L*BCU<<16)
	adc	a, l		; a=H*C+L*B+(HLU*C+H*B+L*BCU<<8)+(E*C+HLU*B+H*BCU+L*A<<16)>>16
	ld	d, ixl		;		 d =L
	ld	e, c		;		 de=LC
	mlt	de		;		ude=L*C
	add	hl, de		;				uhl=L*C+(H*C+L*B<<8)+(HLU*C+H*B+L*BCU<<16)
	adc	a, 0		; a=L*C+(H*C+L*B<<8)+(HLU*C+H*B+L*BCU<<16)+(E*C+HLU*B+H*BCU+L*A<<24)>>24
	pop	ix		;						uix=UIX				--
	pop	de		;		ude=UDE							--
	ld	e, a		;		  e=H*C+L*B+(HLU*C+H*B+L*BCU<<8)+(E*C+HLU*B+H*BCU+L*A<<16)>>16
	pop	af		; a=A								--
	ret

; (EUHL*AUBC)&0xFFFFFFFF=L*C+(H*C+L*B<<8)+(HLU*C+H*B+L*BCU<<16)+(E*C+HLU*B+H*BCU+L*A<<24)+(E*B+HLU*BCU+H*A<<32)+(E*BCU+HLU*A<<40)+(E*A<<48)&0xFFFFFFFF
;			=L*C+(H*C+L*B<<8)+(HLU*C+H*B+L*BCU<<16)+(E*C+HLU*B+H*BCU+L*A<<24)&0xFFFFFFFF

