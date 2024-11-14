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
; Performs 48-bit bitwise or
;
; Returns:
; ude:uhl = ude:uhl | uiy:ubc

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__i48or
__i48or:
	push	af

	; Deal with Upper Byte
	push	hl
	push	bc
	push	de
	scf
	sbc	hl, hl
	add	hl, sp					; uhl = &iyu
	push	iy

	ld	de, 3
	ld	a, (hl) 				; a = iyu
	add	hl, de
	or	a, (hl) 				; a |= deu
	ld	(hl), a 				; deu = a

	add	hl, de
	ld	a, (hl) 				; a = bcu
	add	hl, de
	or	a, (hl) 				; a |= hlu
	ld	(hl), a 				; hlu = a

	; Load values back into registers and process low and high bytes
	pop	bc
	pop	de

	ld	a, d
	or	a, b 					; = iyh
	ld	d, a

	ld	a, e
	or	a, c 					; = iyl
	ld	e, a

	pop	bc
	pop	hl

	ld	a, h
	or	a, b
	ld	h, a

	ld	a, l
	or	a, c
	ld	l, a

	pop	af
	ret