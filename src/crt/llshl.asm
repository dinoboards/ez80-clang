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

	section	.text,"ax",@progbits
	.global	__llshl
__llshl:
; Suboptimal for large shift amounts
	push	af
	ld	a, b

	push	hl
	ld	hl, 9
	add	hl, sp
	ld	b, (hl)
	pop	hl

	inc	b
	jr	.begin

.loop:
	add	hl, hl
	ex	de, hl
	adc	hl, hl
	ex	de, hl
	rl	c
	rla
.begin:
	djnz	.loop

	ld	b, a
	pop	af
	ret
