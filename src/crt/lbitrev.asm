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
; This function reverses the bits of a 24-bit number
; Arguments: HL = 24-bit number
; Returns: HL = reversed bits of HL
;--------------------------------------------------------------
	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__lbitrev
__lbitrev:
	push	af
	ld	a, h				; a=H
	ld	h, l				; uhl=[HLU]LL
	call	__internal_bitrev_two_bytes	; a=HLU', uhl=LLH'
	ld	h, l
	ld	l, a				; uhl=LH'[HLU']
	ld	a, e				; a=E
	call	__internal_bitrev_two_bytes	; a=L', uhl=H'[HLU']E'
	ld	e, a				; e=L'
	pop	af
	ret

	extern	__internal_bitrev_two_bytes
