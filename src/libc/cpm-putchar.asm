	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_putchar
	extern	_cpm_c_write

_putchar:
	jp	_cpm_c_write

