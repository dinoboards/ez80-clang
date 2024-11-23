	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_sfirst
	extern 	cpm_f_status_03

_cpm_f_sfirst:
	ld	c, F_SFIRST
	jp	cpm_f_status_03

