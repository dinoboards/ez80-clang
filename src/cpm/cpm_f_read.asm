	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_read
	extern cpm_f_status_00

_cpm_f_read:
	ld	c, F_READ
	jp	cpm_f_status_00

