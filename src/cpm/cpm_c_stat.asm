	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_stat

_cpm_c_stat:
	ld	c, C_STAT
	jp	cpm_bdos

	extern	cpm_bdos
