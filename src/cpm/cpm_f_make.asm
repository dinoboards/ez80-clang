	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_make
	extern	cpm_f_status_03

_cpm_f_make:
	ld	c, F_MAKE
	jp	cpm_f_status_03

