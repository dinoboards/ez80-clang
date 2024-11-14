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
; Performs 48-bit signed comparison
;
; Arguments:
; ude:uhl = left-hand side
; uiy:ubc = right-hand side
;
; Returns:
; S and V flags updated according to comparison

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__i48cmps
__i48cmps:
	push hl
	push de
	or a, a
	sbc hl, bc ; compare hl to bc
	ex de, hl ; hl = de
	lea de, iy+0 ; de = iy
	sbc hl, de ; compare de to iy
	pop de
	pop hl
	ret

