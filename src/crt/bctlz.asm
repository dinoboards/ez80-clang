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
; bctlz - count leading zeros in the 8-bit value in register A
;
;--------------------------------------------------------------
	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__bctlz
__bctlz:
	push	hl

	scf
	sbc	hl, hl

.loop:
	rla
	inc	hl
	jr	nc, .loop

	ld	a, l
	pop	hl
	ret
