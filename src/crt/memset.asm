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
	.global	_memset
_memset:
	pop	iy
	pop	hl
	pop	de
	pop	bc
	push	bc
	push	de
	push	hl
	push	iy
	cpi
	add	hl, bc
	ret	c
	dec	hl
	ld	(hl), e
	ret	po
	push	hl
	pop	de
	dec	de
	lddr
	ret
