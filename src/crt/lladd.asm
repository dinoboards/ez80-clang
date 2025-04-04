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
	.global	__lladd
__lladd:
	push	iy
	ld	iy, 0
	add	iy, sp
	push	bc
	ld	bc, (iy+6)
	add	hl, bc
	ex	de, hl
	ld	bc, (iy+9)
	adc	hl, bc
	ex	de, hl
	pop	bc
	jr	nc, .nc48
	inc	bc
.nc48:
	ld	iy, (iy+12)
	add	iy, bc
	lea	bc, iy+0
	pop	iy
	ret
