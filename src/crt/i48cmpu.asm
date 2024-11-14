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
; Performs 48-bit unsigned comparison
;
; Arguments:
; ude:uhl = left-hand side
; uiy:ubc = right-hand side
;
; Returns:
; Z and C flags updated according to comparison

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__i48cmpu
__i48cmpu:
	push	hl
	or	a, a
	lea	hl, iy+0
	sbc	hl, de ; subtract IY - DE, which is the other way around
	ccf ; complement carry
	pop	hl
	ret	nz
	or	a, a
	sbc	hl, bc ; subtract the low parts the normal way
	add	hl, bc ; causes the same carry, preserves Z
	ret ; don't complement carry
