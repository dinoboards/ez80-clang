	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_drv_get

_cpm_drv_get:
	ld	c, DRV_GET
	call	cpm_bdos
	ld	l, a
	ret

	extern	cpm_bdos
