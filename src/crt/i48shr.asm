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
; Performs 48-bit shift right
;
; Returns:
; ude:uhl = ude:uhl>>c

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__i48shrs
__i48shrs:
	inc	c
	dec	c
	ret	z
	cp	a, a ; Set Z flag
	db	$C2 ; inc c \ dec c \ ret z -> jp nz,*

	.global	__i48shru
__i48shru:
	inc	c
	dec	c
	ret	z
	; NZ for unsigned shift, Z for signed shift
	push	bc
	ld	b, c
	push	af
	push	de
	push	hl
	ld	hl, 5
	add	hl, sp
	ld	c, (hl)
	dec	hl
	dec	hl
	dec	hl
	ld	a, (hl)
	ex	(sp), hl
	jr	z, .loop
	srl	c
	jr	.midloop
.loop:
	sra	c
.midloop:
	rr	d
	rr	e
	rra
	rr	h
	rr	l
	djnz	.loop
	ex	(sp), hl
	ld	(hl), a
	inc	hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
	inc	hl
	ld	(hl), c
	pop	hl
	pop	de
	pop	af
	pop	bc
	ret
