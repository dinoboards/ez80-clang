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
; Performs 48-bit byte reversal
;
; Returns:
; ude:uhl = ude:uhl with order of bytes reversed

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__i48bswap
__i48bswap:
	; Line up the reversed data on the stack
	push	hl
	ld	h, e
	ld	l, d
	ex	(sp), hl
	ld	d, l
	ld	e, h
	push	de
	push	hl
	; -1: hlu
	; -2: e
	; -3: d
	; -4: deu
	; -5: l
	; -6: h
	; -7: hlu
	; -8: h
	; -9: l

	; Misalign the stack and pop into the correct registers
	inc	sp
	inc	sp
	pop	de
	pop	hl
	inc	sp
	ret
