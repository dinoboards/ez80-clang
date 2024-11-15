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
	.global	__sbitrev
__sbitrev:
	push	af
	ld	a, l				; a=L
	push	hl
	dec	sp
	pop	hl
	inc	sp				; uhl=HL?
	call	__internal_bitrev_two_bytes	; a=H', uhl=L?L'
	ld	h, l
	ld	l, a				; hl=L'H'
	pop	af
	ret

	extern	__internal_bitrev_two_bytes
