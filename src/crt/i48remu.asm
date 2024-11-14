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
; Performs 48-bit unsigned division and remainder
; Arguments: ude:uhl = dividend, uiy:ubc = divisor
; Result in ude:uhl
;--------------------------------------------------------------
	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__i48remu

__i48remu:
	push	iy
	push	bc

	call	__i48dvrmu
	lea	de, iy+0
	or	a, a
	sbc	hl, hl
	add	hl, bc

	pop	bc
	pop	iy
	ret

	extern	__i48dvrmu
