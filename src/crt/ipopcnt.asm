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
; Performs 16-bit popcount
; Arguments: uhl
; Result in A
;--------------------------------------------------------------
	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__ipopcnt
__ipopcnt:
	push	hl
	; Calculate 8-popcount(L)-popcount(HLU), and set HLU=H, L=0
	call	__popcnt_common_init_full
	; Subtract output carry and H (which will be added back in)
	sbc	a, h
	; Accumulate popcount(L)-popcount(HLU)+H-L=H-popcount(HLU)
	call	__popcnt_common_iter
	; Subtract final value from 8, and accumulate output carry
	cpl
	adc	a, 9
	pop	hl
	ret

	extern	__popcnt_common_init_full, __popcnt_common_iter
