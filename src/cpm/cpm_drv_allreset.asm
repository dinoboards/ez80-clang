	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_drv_allreset

_cpm_drv_allreset:
	ld	c, DRV_ALLRESET
	jp	cpm_bdos

	extern	cpm_bdos
