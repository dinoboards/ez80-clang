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
; Performs 48-bit bit reversal
;
; Returns:
; ude:uhl = ude:uhl bits reversed

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__i48bitrev
__i48bitrev:
	push	af
	ld	a, l				; a=L
	call	__internal_bitrev_two_bytes	; a=HLU', uhl=HLL'
	ld	h, l
	ld	l, a				; uhl=HL'[HLU']
	ld	a, e				; a=E
	call	__internal_bitrev_two_bytes	; a=H', uhl=L'[HLU']E'
	ld	e, a				; ude=[DEU]DH'
	ld	a, d				; a=D
	ld	d, l				; ude=[DEU]E'H'
	ld	l, h
	ld	h, e				; uhl=L'H'[HLU']
	ex	de, hl				; uhl=[DEU]E'H', ude=L'H'[HLU']HLU'E'
	call	__internal_bitrev_two_bytes	; a=DEU', uhl=E'H'D'
	ld	h, l
	ld	l, a				; uhl=E'D'[DEU']
	pop	af
	ret

	extern	__internal_bitrev_two_bytes
