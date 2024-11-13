	include "src/cpm/cpm.inc"

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_cpm_get_iobyte

_cpm_get_iobyte:
	LD	C, GET_IOBYTE
	CALL	cpm_bdos
	LD	L, A
	RET

	extern	cpm_bdos
