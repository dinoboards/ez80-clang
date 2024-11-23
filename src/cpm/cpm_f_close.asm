	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_close
	extern	cpm_f_status_03

_cpm_f_close:
	ld	c, F_CLOSE
	jp	cpm_f_status_03
