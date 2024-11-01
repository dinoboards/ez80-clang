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

	section	.text
	.global	__lshru

__lshru:
; Suboptimal for large shift amounts
; CC: if C!=0: C*(15*r(PC)+3*r(SPL)+3*w(SPL)+4)+17*r(PC)+9*r(SPL)+6*w(SPL)+2
;     if C==0: 4*r(PC)+3*r(SPL)+2
	inc	l
	dec	l
	ret	z
	push	hl
	push	bc
	ld	b, l
	or	a, a
	sbc	hl, hl
	add	hl, sp
.loop:
	srl	a
	jp	__lshrs_hijack_lshru

	extern	__lshrs_hijack_lshru

