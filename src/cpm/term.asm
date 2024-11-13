	include "src/cpm/cpm.inc"

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_cpm_term

_cpm_term:
	LD	C, P_TERMCPM
	LD	DE, 0
	LD	HL, 0
	JP	cpm_bdos

	extern	cpm_bdos
