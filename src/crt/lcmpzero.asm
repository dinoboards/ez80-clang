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
; This function compares a 32-bit number to zero
; Arguments: E:UHL = 32-bit number
; Result: Z flag set if E:UHL == 0, otherwise Z flag reset
;--------------------------------------------------------------
	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__lcmpzero
__lcmpzero:
	inc	e
	dec	e
	ret	nz
	add	hl, bc
	or	a, a
	sbc	hl, bc
	ret	p
	inc	e
	dec	de
	ret
