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
	.global	__lpopcnt
__lpopcnt:
	push	hl
	; Calculate 8-popcount(L)-popcount(HLU), and set HLU=H
	call	__popcnt_common_init_full
	; Save the current count in H
	ld	h, a
	; Prepare to accumulate 8-popcount(E)-popcount(HLU)
	ld	a, e
	cpl
	ld	l, a
	; Subtract output carry and an additional H, the adjusted call adds H*2-L
	sbc	a, h
	call	__popcnt_common_iter_adjusted
	; Subtract final value from 16, and accumulate output carry
	cpl
	adc	a, 17
	pop	hl
	ret

	extern	__popcnt_common_init_full, __popcnt_common_iter_adjusted
