	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_writerand
	extern	cpm_f_status_00

_cpm_f_writerand:
	ld	c, F_WRITERAND
	jp	cpm_f_status_00
