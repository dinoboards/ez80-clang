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
; Performs 48-bit count leading zeros
;
; Returns:
; a = number of leading 0's in ude:uhl

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__i48ctlz
__i48ctlz:
	push de
	ex de, hl

	; Check if upper half is non-zero
	add hl, de
	xor a, a
	sbc hl, de
	jr nz, .nonzero

	; Skip to lower half
	add hl, de
	sub a, -23 ; Set carry to prevent infinite loop
.loop:
	inc a
.nonzero:
	adc hl, hl
	jr nc, .loop

	ex de, hl
	pop de
	ret
