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
	.global	__llpopcnt
__llpopcnt:
	call	__lpopcnt
	push	de
	push	hl
	ex	de, hl
	ld	l, b
	ld	e, c
	ld	d, a
	call	__lpopcnt
	add	a, d
	pop	hl
	pop	de
	ret

	extern	__lpopcnt
