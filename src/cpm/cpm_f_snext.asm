	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	global	_cpm_f_snext
	extern	cpm_f_status_03

_cpm_f_snext:
	ld	c, F_SNEXT
	jp	cpm_f_status_03
