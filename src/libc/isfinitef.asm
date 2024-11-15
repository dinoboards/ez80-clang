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

	section	.text, "ax", @progbits
	.global	__isfinitef
__isfinitef:
	pop	bc
	pop	hl
	pop	de
	push	de
	push	hl
	push	bc
	add	hl, hl
	ld	a, e
	rla
	add	a, 1
	sbc	hl, hl
	inc	hl
	ret

