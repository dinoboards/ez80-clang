	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_get_iobyte

_cpm_get_iobyte:
	ld	c, GET_IOBYTE
	call	cpm_bdos
	ld	l, a
	ret

	extern	cpm_bdos
