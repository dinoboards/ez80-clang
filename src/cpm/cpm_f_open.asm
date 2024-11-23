	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_open
	extern	cpm_f_status_03

_cpm_f_open:
	ld	c, F_OPEN
	jp	cpm_f_status_03
