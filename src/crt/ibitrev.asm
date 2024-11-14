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
; Performs 48-bit bit reverse
; Arguments: ude:uhl
; Result in ude:uhl
;--------------------------------------------------------------
	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__ibitrev
__ibitrev:
	push	af
	ld	a, l				; a=L
	call	__internal_bitrev_two_bytes	; a=HLU', uhl=HLL'
	ld	h, l
	ld	l, a				; uhl=HL'[HLU']
	call	__internal_bitrev_two_bytes	; a=H', uhl=L'[HLU'][HLU]
	ld	l, h
	ld	h, a				; uhl=L'H'[HLU']
	pop	af
	ret

	extern	__internal_bitrev_two_bytes
