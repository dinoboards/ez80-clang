	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_write

_cpm_c_write:
	call	__frameset0
	ld	e, (ix+6)
	ld	c, C_WRITE
	call	cpm_bdos_adl
	pop	ix
	ret

	extern	cpm_bdos_adl
