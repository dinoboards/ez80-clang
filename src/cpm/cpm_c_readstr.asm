	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_readstr

_cpm_c_readstr:
	ld	iy, 0
	add	iy, sp
	ld	de, (IY+3)		; must be within the current MBASE segment
	ld	c, C_READSTR
	call	cpm_bdos
	push	de
	pop	hl
	ret

	extern	cpm_bdos
