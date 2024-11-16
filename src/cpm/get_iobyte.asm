	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_get_iobyte

_cpm_get_iobyte:
	push	ix
	ld	c, GET_IOBYTE
	call.sis cpm_bdos_z80 & 0xFFFF
	ld	l, a
	pop	ix
	ret

	extern	cpm_bdos_z80
