	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_drv_set

_cpm_drv_set:
	call	__frameset0
	ld	e, (ix+6)
	ld	c, DRV_SET
	call	cpm_bdos_adl
	pop	ix
	ret

	extern	cpm_bdos_adl
