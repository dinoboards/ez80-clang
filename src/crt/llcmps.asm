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
	.global	__llcmps
__llcmps:
	push	iy
	ld	iy, 0
	add	iy, sp
	push	bc
	push	hl
	ld	l, c
	ld	h, b
	ld	bc, (iy+12)
	sbc.s	hl, bc
	pop	hl
	jr	nz, .finish
	ld	bc, (iy+9)
	ex	de, hl
	sbc	hl, bc
	add	hl, bc
	ex	de, hl
	jr	nz, .finish_unsigned
	ld	bc, (iy+6)
	sbc	hl, bc
	add	hl, bc
.finish_unsigned:
	ld	b, a
	sbc	a, a
	ld	a, b
.finish:
	pop	bc
	pop	iy
	ret
