; (c) Copyright 2007-2008 Zilog, Inc.
;   char * strcpy(void * d, void * s)


	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_strcpy

_strcpy:
	ld	hl, 6
	add	hl, sp
	ld	bc, (hl)
	dec	hl
	dec	hl
	dec	hl
	ld	de, (hl)		;assumed de has not been changed in _strlen
	push	de
	push	bc
	call	_strlen
	push	hl
	pop	bc
	inc	bc
	pop	hl
	ldir
	pop	hl
	ret

	extern	_strlen

