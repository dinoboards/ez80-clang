	.assume adl=1

	section	.text,"ax",@progbits
	.global	_fabs, _fabsf

_fabs:
_fabsf:
	pop	bc
	pop	hl
	pop	de
	push	de
	push	hl
	push	bc
	res	7,e
	ret
