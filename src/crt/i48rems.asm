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
	.global	__i48rems
; Result in ude:uhl
__i48rems:
	push	iy
	push	bc

	; divisor sign check
	push	hl
	lea	hl, iy+0
	add	hl, hl
	call	c, __uiyubcNeg

	; dividend sign check
	sbc	hl, hl
	adc	hl, de
	pop	hl
	push	af
	call	m, __i48neg
	pop	af

	call	__i48dvrmu
	lea	de, iy+0
	push	bc
	pop	hl
	; negate remainder if dividend was negative
	call	m, __i48neg

	pop	bc
	pop	iy
	ret

	extern	__i48dvrmu
	extern	__i48neg
	extern	__uiyubcNeg
