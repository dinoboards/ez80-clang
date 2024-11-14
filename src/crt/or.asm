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
	.global	__lor

LD_A_N = 0x3E

__lor:
; CC: 28*r(PC)+11*r(SPL)+10*w(SPL)+1
	push	af
	or	a, e
	ld	e, a

	db	LD_A_N	; push af -> ld a,*

	.global	__ior

__ior:
; CC: 24*r(PC)+11*r(SPL)+10*w(SPL)+1
	push	af
.hijack_lor:
	push	hl
	scf
	sbc	hl, hl
	add	hl, sp
	push	bc
	ld	a, (hl)
	inc	hl
	ld	sp, hl
	inc	hl
	inc	hl
	or	a, (hl)
	ld	(hl), a
	pop	hl
	ld	a, h
	or	a, b
	ld	h, a
	ld	a, l
	or	a, c
	ld	l, a
	pop	af
	ret
