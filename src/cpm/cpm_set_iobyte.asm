	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_set_iobyte

_cpm_set_iobyte:
	ld	iy, 0
	add	iy, sp
	ld	e, (IY+3)
	ld	c, SET_IOBYTE
	jp	cpm_bdos

	extern	cpm_bdos
