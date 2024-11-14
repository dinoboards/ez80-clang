	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_a_read

_cpm_a_read:
	ld	c, A_READ
	jp	cpm_bdos

	extern	cpm_bdos
