	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_size
	extern	cpm_f_status_03

_cpm_f_size:
	ld	c, F_SIZE
	jp	cpm_f_status_00
