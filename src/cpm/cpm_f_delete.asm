	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_delete
	extern	cpm_f_status_03

_cpm_f_delete:
	ld	c, F_DELETE
	jp	cpm_f_status_03
