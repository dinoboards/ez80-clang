	include "src/cpm/cpm.inc"

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_cpm_read

_cpm_read:
	LD	C, C_READ
	JP	cpm_bdos

	extern	cpm_bdos