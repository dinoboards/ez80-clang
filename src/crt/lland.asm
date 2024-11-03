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
	.global	__lland
__lland:
; CC: 62*r(PC)+25*r(SPL)+14*w(SPL)+1
	push	af
	push	iy
	ld	iy, 0
	add	iy, sp
	push	hl
	push	de
	lea	hl, iy + 16
	ld	a, b
	and	a, (hl)
	ld	b, a
	dec	hl
	ld	a, c
	and	a, (hl)
	ld	c, a
	dec	hl
	lea	de, iy - 4
	ld	a, (de)
	and	a, (hl)
	ld	(de), a
	pop	de
	dec	hl
	ld	a, d
	and	a, (hl)
	ld	d, a
	dec	hl
	ld	a, e
	and	a, (hl)
	ld	e, a
	dec	hl
	ld	a, (iy - 1)
	and	a, (hl)
	ld	(iy - 1), a
	pop	hl
	ld	a, h
	and	a, (iy + 10)
	ld	h, a
	ld	a, l
	and	a, (iy + 9)
	ld	l, a
	pop	iy
	pop	af
	ret