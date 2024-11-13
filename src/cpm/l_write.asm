	include "src/cpm/cpm.inc"

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_cpm_l_write

_cpm_l_write:
	LD	IY, 0
	ADD	IY, SP
	LD	E, (IY + 3)
	LD	C, L_WRITE
	JP	cpm_bdos

	extern	cpm_bdos
