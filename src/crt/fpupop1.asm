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
	.global	__fpupop1
__fpupop1:
	push	ix
	ld	ix, 0
	add	ix, sp
	push	bc
	rlc	(ix-1)	;move high-bit to low-bit
	scf
	rr	(ix-1)	;carry = exponent low-bit, high-bit = 1
	pop	bc		;restore modified mantissa
	rl	a		;compute exponent, carry = sign
	ld	d, 0
	jr	nz, nzero	;skip if exponent non-zero

	ld	bc, 0		;clear mantissa
	or	a, a		;clear carry
nzero:
	rl	d		;set 1 if negative operand
	or	a, a		;set Z/NZ
	pop	ix
	ret
