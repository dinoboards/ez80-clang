; (c) Copyright 2007-2008 Zilog, Inc.
;   size_t strlen(char *s)

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_strlen

_strlen:
	ld	hl, 3
	add	hl, sp
	ld	hl, (hl)
	xor	a, a
	ld	bc, 0
	cpir
	or	a, a
	sbc	hl, hl
	scf
	sbc	hl, bc
	ret

