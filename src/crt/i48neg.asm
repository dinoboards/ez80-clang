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
; Performs 48-bit unary minus
;
; Returns:
; ude:uhl = -ude:uhl

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__i48neg
__i48neg:
	or a, a
	sbc hl, de ; hl = HL - DE
	ex de, hl ; hl = DE, de = HL - DE
	add hl, de ; hl = HL
	add hl, de ; hl = HL * 2 - DE
	ex de, hl ; hl = HL - DE, de = HL * 2 - DE
	or a, a
	sbc hl, de ; hl = -HL, set Z flag
	ex de, hl ; hl = HL * 2 - DE, de = -HL
	add hl, de ; hl = HL - DE
	add hl, de ; hl = -DE
	ex de, hl ; hl = -HL, de = -DE
	ret z ; Return if -HL = 0, meaning no carry when negating the low half
	dec de ; Carry adjustment
	ret

;Used by i48divs and i48rems, uiy:ubc = -uiy:ubc
	.global  __uiyubcNeg
__uiyubcNeg:
	push hl
	or a, a
	sbc hl, hl
	sbc hl, bc ; hl = 0 - BC = -BC
	push hl
	add hl, bc ; hl = 0, causes the same carry
	lea bc, iy+0
	sbc hl, bc ; hl = 0 - IY - c
	pop bc ; bc = -BC
	ex (sp), hl ; hl = HL
	pop iy ; iy = -IY - c
	ret
