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
	.global	__spopcnt
__spopcnt:
	; Set HLU=H and H=L, while saving HL on the stack
	push	hl
	dec	sp
	ex	(sp), hl
	; Calculate 8-popcount(H)-popcount(HLU)
	ld	a, h
	call	__popcnt_common_init
	; Subtract final value from 8, and accumulate output carry
	cpl
	adc	a, 9
	pop	hl
	inc	sp
	ret

	extern	__popcnt_common_init
