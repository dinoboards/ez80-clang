	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_drv_allreset

_cpm_drv_allreset:
	push	ix
	ld	c, DRV_ALLRESET
	call	cpm_bdos_adl
	pop	ix
	ret


	extern	cpm_bdos_adl
