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
; Performs 48-bit shift left
;
; Returns:
; ude:uhl = ude:uhl<<c

.assume	adl=1

	section	.text, "ax", @progbits
	.global	__i48shl
__i48shl:
	push	bc
	ld	b, a

	ld	a, e ; Accumulate E in A to reduce register exchanges and preserve Z
	srl	c
	jr	nc, .bit0
	; ude:uhl<<1
	add	hl, hl
	rla
	ex	de, hl
	add	hl, hl
	ex	de, hl
.bit0:
	srl	c
	jr	nc, .bit1
	; ude:uhl<<2
	add	hl, hl
	rla
	add	hl, hl
	rla
	ex	de, hl
	add	hl, hl
	add	hl, hl
	ex	de, hl
.bit1:
	srl	c
	jr	nc, .bit2
	; ude:uhl<<4
	add	hl, hl
	rla
	add	hl, hl
	rla
	add	hl, hl
	rla
	add	hl, hl
	rla
	ex	de, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ex	de, hl
.bit2:
	ld	e, a

	jr	z, .done ; Early out when no byte shift is needed
	; Subtract the byte shift amount from 9
	ld	a, 9
	sub	a, c ; Clears carry for valid shift amounts

	; Push the result shifted left by 48 as a 96-bit value on the stack
	push	de
	push	hl
	sbc	hl, hl
	push	hl
	push	hl

	; Offset and read the byte-shifted value
	ld	l, a
	add	hl, sp
	ld	de, (hl)
	dec	hl
	dec	hl
	dec	hl
	ld	hl, (hl)

	pop	af
	pop	af
	pop	af
	pop	af
.done:
	ld	a, b
	pop	bc
	ret