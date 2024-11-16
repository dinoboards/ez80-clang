	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_read

_cpm_c_read:
	push	ix
	ld	c, C_READ
	call.sis cpm_bdos_z80 & 0xFFFF
	pop	ix
	ret

	extern	cpm_bdos_z80
