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
	.global	__i48divs
; Result in ude:uhl
__i48divs:
	push af
	push iy
	push bc

	; divisor sign check
	push hl
	lea hl, iy+0
	add hl, hl
	sbc a, a
	call c, __uiyubcNeg

	; dividend sign check
	ld hl, $800000
	add hl, de
	pop hl
	rla
	rrca
	call c, __i48neg

	call __i48dvrmu

	; negate quotient if exactly one of the dividend and divisor is negative
	add a, a
	call pe, __i48neg

	pop bc
	pop iy
	pop af
	ret

	extern	__i48dvrmu
	extern	__i48neg
	extern	__uiyubcNeg
