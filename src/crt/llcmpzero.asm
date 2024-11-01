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
	.global	__llcmpzero
__llcmpzero:
	inc	b
	dec	b
	ret	nz
	inc.s	bc
	dec	c
	jr	nz, .p_nz
	or	a, a
	sbc	hl, bc
	jr	nz, .p_nz
	sbc	hl, de
	ret	z
	add	hl, de
.p_nz:
	inc	b
	ld	b, 0
	ret
