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
	.global	__ftoll, __ftoull, __dtoll, __dtoull
__ftoll:
__ftoull:
__dtoll:
__dtoull:
	ld	d, a
	push	iy, de, hl
	call	__ftoll_c
	pop	af, af, iy
	ret

	extern	__ftoll_c
