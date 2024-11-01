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
	.global	__lcmps

__lcmps:
	push	de
	ld	d, a
	ld	a, e
	sub	a, d
	jr	nz, .finish
	sbc	hl, bc
	add	hl, bc
	sbc	a, a
.finish:
	ld	a, d
	pop	de
	ret

