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
; Performs 48-bit comparison with 0
;
; Returns:
; z status flag set if ude:uhl == 0, s status flag set if ude:uhl is negative

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__i48cmpzero
__i48cmpzero:
	;check msb's == 0
	ex	de, hl
	add	hl, de
	or	a, a
	sbc	hl, de ; z set if de = 0, s set if de is negative (z also reset)
	ex	de, hl
	ret	nz
	;check lsb's == 0
	;in this path, de = 0 and carry is reset
	sbc	hl, de
	ret	p
	;special case if bit 23 is set
	inc	e ; reset z and s flags
	dec	de
	ret
