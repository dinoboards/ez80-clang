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
	.global	__fpupop2

__fpupop2:
	push	bc
	ld	bc, 0800000h
	add	hl, bc
	jr	nc, ncarry
	add	hl, bc
	scf
ncarry:
	ld	d, c
	pop	bc
	rl	e
	jr	nz, nzero
	or	a, a
	sbc	hl, hl
nzero:
	rl	d
	inc	e
	dec	e
	ret
