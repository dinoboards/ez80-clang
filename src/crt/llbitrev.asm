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
	.global	__llbitrev
__llbitrev:
	push	af
	ld	a, d				; a=D
	call	__internal_bitrev_two_bytes	; a=HLU', uhl=HLD'
	ld	d, a				; ude=[DEU][HLU']E
	ld	a, c				; a=C
	call	__internal_bitrev_two_bytes	; a=H', uhl=LD'C'
	ld	c, a				; bc=BH'
	ld	a, e				; a=E
	ex	de, hl
	call	__internal_bitrev_two_bytes	; a=DEU', ude=[HLU']EE'
	ex	de, hl
	ld	d, e
	ld	e, h				; ude=[HLU']E'D'
	ld	h, a				; uhl=L[DEU']C'
	ld	a, b				; a=B
	call	__internal_bitrev_two_bytes	; a=L', uhl=[DEU']C'B'
	ld	b, a				; bc=L'H'
	pop	af
	ret

	extern	__internal_bitrev_two_bytes
