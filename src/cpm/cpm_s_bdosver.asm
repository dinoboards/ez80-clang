	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_s_bdosver

_cpm_s_bdosver:
	ld	c, S_BDOSVER
	call	cpm_bdos
	ld	l, a
	ret

	extern	cpm_bdos
