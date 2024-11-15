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
	.global	__lnot

__lnot:
	push	af
	ld	a, e	; a=E
	cpl		; a=~E
	ld	e, a	; e=~E
	pop	af
	push	de
	add	hl, de	; uhl=UHL+x
	ex	de, hl	; ude=UHL+x, uhl=x
	scf
	sbc	hl, de	; uhl=x-(UHL+x)-1
			;    =x-UHL-x-1
			;    =-UHL-1
			;    =~UHL
	pop	de
	ret
