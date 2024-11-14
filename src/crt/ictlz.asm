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
; Performs 48-bit count leading zeros
; Arguments: ude:uhl
; Result in A
;--------------------------------------------------------------
	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__ictlz
__ictlz:
	push	hl

	scf
	sbc	a, a

.loop:
	adc	hl, hl
	inc	a
	jr	nc, .loop

	pop	hl
	ret
