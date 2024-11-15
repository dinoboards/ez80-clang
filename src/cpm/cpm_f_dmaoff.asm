	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_f_dmaoff

_cpm_f_dmaoff:
	ld	iy, 0
	add	iy, sp
	ld	de, (IY+3)		; must be within the current MBASE segment
	ld	c, F_DMAOFF
	jp	cpm_bdos

	extern	cpm_bdos
