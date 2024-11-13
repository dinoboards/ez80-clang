	include "src/cpm/cpm.inc"

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_cpm_a_read

_cpm_a_read:
	LD	C, A_READ
	JP	cpm_bdos

	extern	cpm_bdos
