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

	section	.text,"ax",@progbits
	.global	__llsub
__llsub:
	push	iy
	ld	iy, 0
	add	iy, sp
	push	bc
	ld	bc, (iy + 6)
	sbc	hl, bc
	ex	de, hl
	ld	bc, (iy + 9)
	sbc	hl, bc
	ex	de, hl
	ex	(sp), hl
	ld	bc, (iy + 12)
	sbc	hl, bc
	ld	c, l
	ld	b, h
	pop	hl
	pop	iy
	ret
