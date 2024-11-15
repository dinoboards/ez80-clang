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
	.global	_copysign, _copysignf
_copysign:
_copysignf:
	pop	bc
	pop	hl
	pop	de
	ld	a, e
	pop	de
	pop	de
	push	de
	push	de
	push	de
	push	hl
	push	bc
	xor	a, e
	and	a, $7F
	xor	a, e
	ld	e, a
	ret

