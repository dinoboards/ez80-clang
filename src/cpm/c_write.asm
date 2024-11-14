	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_write

_cpm_c_write:
	ld	iy, 0
	add	iy, sp
	ld	e, (IY+3)
	ld	c, C_WRITE
	jp	cpm_bdos

	extern	cpm_bdos
