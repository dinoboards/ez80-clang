	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_drv_set

_cpm_drv_set:
	ld	iy, 0
	add	iy, sp
	ld	e, (IY+3)
	ld	c, DRV_SET
	jp	cpm_bdos

	extern	cpm_bdos
