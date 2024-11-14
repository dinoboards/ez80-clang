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
	.global	__llshru
__llshru:
; Suboptimal for large shift amounts
	push	af
	push	iy
	ld	iy, 0
	add	iy, sp
	ld	a, (iy+9)
	or	a, a
	jp	z, __llshrs_finish
	push	de
	push	hl
	srl	b
	jp	__llshrs_hijack_llshru

	extern	__llshrs_finish
	extern	__llshrs_hijack_llshru
