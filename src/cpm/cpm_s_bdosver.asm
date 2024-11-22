	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_s_bdosver

_cpm_s_bdosver:
	push	ix
	ld	c, S_BDOSVER
	call	cpm_bdos_adl
	ld	l, a
	pop	ix
	ret

	extern	cpm_bdos_adl
