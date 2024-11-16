	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_drv_get

_cpm_drv_get:
	push	ix
	ld	c, DRV_GET
	call.sis cpm_bdos_z80 & 0xFFFF
	ld	l, a
	pop	ix
	ret

	extern	cpm_bdos_z80
