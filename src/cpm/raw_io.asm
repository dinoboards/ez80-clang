	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_rawio

_cpm_c_rawio:
	push	ix
	ld	c, C_RAWIO
	ld	e, $FF
	call.sis cpm_bdos_z80 & 0xFFFF
	ld	l, a
	pop	ix
	ret

	extern	cpm_bdos_z80
