;--------------------------------------------------------------
;
;	C RUNTIME FUNCTION
;	For the eZ80 Clang cross compiler
;--------------------------------------------------------------
;
;	  	Multiply 2 64 bit numbers
;
; Calling Convention:
;	CallingConv::Z80_LibCall
;
; INPUTS:
;	Operand1:
;		  BCDEHL : 64 bit number (upper of BC is ignored)
;	Operand2:
;		  Stack Frame: 9 bytes, 64 bit number
;
; OUTPUTS:
;	result:	  BCDEHL : 64 bit result
;
;--------------------------------------------------------------

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__llmuls, __llmulu
__llmuls:
__llmulu:
	push	ix
	push	iy
	push	af
	ld	ix, 0
	add	ix, sp

	ld	(ix - 9), hl			; low of A (24)
	ld	(ix - 6), de			; mid of A (24)
	ld	(ix - 3), bc			; high of A (16)

	lea	hl, ix - 28
	ld	sp, hl

	xor	a
	sbc	hl, hl
	ld	(ix - 21), hl			; result = 0
	ld	(ix - 24), hl
	ld	(ix - 27), hl			; result (IX-21 to IX-27)

	ld	a, 64
	; for (uint8_t i = 0; i < 64; i++)
loop:
	ld	hl, (ix - 9)			; A (BCDEHL)
	ld	(ix - 6), de			; A (save mid)
	ld	(ix - 3), bc			; A (save high)
	bit	0, l				; test it
	jr	z, skip_add

	ld	bc, (ix + 18)			; B (BCDEHL)
	ld	de, (ix + 15)			; B
	ld	hl, (ix + 12)			; B

	; result += b
	push	bc
	ld	bc, (ix - 21)			; result (low)
	add	hl, bc
	ex	de, hl
	ld	bc, (ix - 24)			; result (mid)
	adc	hl, bc
	ex	de, hl
	pop	bc
	jr	nc, .nc48
	inc	bc
.nc48:
	ld	iy, (ix - 27)			; result (high)
	add	iy, bc
	lea	bc, iy+0

	ld	(ix - 21), hl			; store new result (low)
	ld	(ix - 24), de			; store new result (mid)
	ld	(ix - 27), bc			; store new result (high)

skip_add:
	; a >>= 1;
	sra	(ix - 2)		; (B)
	rr	(ix - 3)		; (C)
	rr	(ix - 4)		; (u of DE)
	rr	(ix - 5)		; (D)
	rr	(ix - 6)		; (E)
	rr	(ix - 7)		; (u of HL)
	rr	(ix - 8)		; (H)
	rr	(ix - 9)		; (L)

	; b <<= 1;
	ld	hl, (ix + 12)		; low of B
	ld	de, (ix + 15)		; mid of B
	ld	bc, (ix + 18)		; high of B
	add	hl, hl
	ex	de, hl
	adc	hl, hl
	ex	de, hl
	rl	c
	rl	b
	ld	(ix + 12), hl
	ld	(ix + 15), de
	ld	(ix + 18), bc

	ld	de, (ix - 6)			; restore A (mid)
	ld	bc, (ix - 3)			; restore A (high)

	; tail for (uint8_t i = 0; i < 64; i++)
	dec	a
	jp	nz, loop

	ld	hl, (ix - 21)
	ld	de, (ix - 24)
	ld	bc, (ix - 27)
	ld	sp, ix
	pop	af
	pop	iy
	pop	ix
	ret
