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
	.global	__bbitrev
__bbitrev:
	push	bc
	ld	b,a 		; b=ABCDEFGH
	rrca 			; a=HABCDEFG
	rrca 			; a=GHABCDEF
	xor	a,b
	and	a,$aa
	xor 	a,b 		; a=GBADCFEH
	ld	b,a 		; b=GBADCFEH
	rrca 			; a=HGBADCFE
	rrca 			; a=EHGBADCF
	rrca 			; a=FEHGBADC
	rrca 			; a=CFEHGBAD
	xor	a,b
	and	a,$66
	xor	a,b 		; a=GFEDCBAH
	rrca 			; a=HGFEDCBA
	pop	bc
	ret

