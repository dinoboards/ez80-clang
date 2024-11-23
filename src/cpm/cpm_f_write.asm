	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_write
	extern	cpm_f_status_00

_cpm_f_write:
	ld	c, F_WRITE
	jp	cpm_f_status_00
