	include "src/cpm/cpm.inc"

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_cpm_rawio

_cpm_rawio:
	LD	C, C_RAWIO
	LD	E, $FF
	CALL	cpm_bdos
	LD	L, A
	RET

	extern	cpm_bdos
