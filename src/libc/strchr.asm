; (c) Copyright 2007-2008 Zilog, Inc.
;   char *strchr(char *s,int c)

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_strchr

_strchr:
	ld	hl, 3
	add	hl, sp
	ld	bc, (hl)
	inc	hl
	inc	hl
	inc	hl
	ld	e, (hl)			;assumed e register has not been changed by _strlen
	push	bc
	call	_strlen
	push	hl
	pop	bc
	inc	bc			;NULL terminating char also included in the search
	pop	hl
	ld	a, e
	cpir
	dec	hl
	ret	z			;if found return HL

_notfound:
	or	a, a
	sbc	hl, hl
	ret


	extern _strlen

