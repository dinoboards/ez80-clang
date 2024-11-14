	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_read

_cpm_c_read:
	ld	c, C_READ
	jp	cpm_bdos

	extern	cpm_bdos
