	include "src/cpm/cpm.inc"

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_cpm_set_iobyte

_cpm_set_iobyte:
	LD	IY, 0
	ADD	IY, SP
	LD	E, (IY + 3)
	LD	C, SET_IOBYTE
	JP	cpm_bdos

	extern	cpm_bdos
