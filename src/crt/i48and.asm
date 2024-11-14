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
; Performs 48-bit bitwise and
;
; Returns:
; ude:uhl = ude:uhl & uiy:ubc

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__i48and
__i48and:
	push af

	; Deal with Upper Byte
	push hl
	push bc
	push de
	scf
	sbc hl, hl
	add hl, sp ; uhl = &iyu
	push iy

	ld de, 3
	ld a, (hl) ; a = iyu
	add hl, de
	and a, (hl) ; a &= deu
	ld (hl), a ; deu = a

	add hl, de
	ld a, (hl) ; a = bcu
	add hl, de
	and a, (hl) ; a &= hlu
	ld (hl), a ; hlu = a

	; Load values back into registers and process low and high bytes
	pop bc
	pop de

	ld a, d
	and a, b ; = iyh
	ld d, a

	ld a, e
	and a, c ; = iyl
	ld e, a

	pop bc
	pop hl

	ld a, h
	and a, b
	ld h, a

	ld a, l
	and a, c
	ld l, a

	pop af
	ret
