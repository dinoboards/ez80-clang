; (c) Copyright 2007-2008 Zilog, Inc.

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_strrchr
	.extern	_strlen

;   char *strrchr(char *s, int c)
_strrchr:
	ld	iy, 0
	add	iy, sp
	ld	bc, (iy+3)
	push	bc
	call	_strlen
	ex	(sp), hl	; hl = s
	pop	bc		; bc = strlen(s)
	add	hl, bc		; hl = hl + strlen(s)
	ld	a, (iy+6)	; a = (char)c
	cpdr
	inc	hl
	jr	z, L_0

	ld	hl, 0
;    	return(NULL);
L_0:
	ret

