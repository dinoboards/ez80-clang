	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_writestr

_cpm_c_writestr:
	ld	iy, 0
	add	iy, sp
	ld	de, (IY+3)		; must be within the current MBASE segment
	ld	c, C_WRITESTR
	jp	cpm_bdos

	extern	cpm_bdos
