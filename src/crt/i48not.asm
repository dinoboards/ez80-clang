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
; Performs 48-bit bitwise not
;
; Returns:
; ude:uhl = ~ude:uhl

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__i48not
__i48not:
	add	hl, de ; hl = HL + DE
	ex	de, hl ; hl = DE, de = HL + DE
	or	a, a
	sbc	hl, de ; hl = -HL
	ex	de, hl ; hl = HL + DE, de = -HL
	add	hl, de ; hl = DE
	add	hl, de ; hl = DE - HL
	ex	de, hl ; hl = -HL, de = DE - HL
	scf
	sbc	hl, de ; hl = -DE - 1
	ex	de, hl ; hl = DE - HL, de = -DE - 1 = ~DE
	add	hl, de ; hl = -HL - 1 = ~HL
	ret
