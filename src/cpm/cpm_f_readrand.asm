	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_readrand
	extern cpm_f_status_00

_cpm_f_readrand:
	ld	c, F_READRAND
	jp	cpm_f_status_00
