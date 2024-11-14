	include "src/cpm/cpm.inc"

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_cpm_c_writestr

_cpm_c_writestr:
	LD	IY, 0
	ADD	IY, SP
	LD	DE, (IY + 3)		; must be within the current MBASE segment
	LD	C, C_WRITESTR
	JP	cpm_bdos

	extern	cpm_bdos
