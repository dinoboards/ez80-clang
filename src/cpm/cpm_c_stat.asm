	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_stat

_cpm_c_stat:
	push	ix
	ld	c, C_STAT
	call.sis cpm_bdos_z80 & 0xFFFF
	pop	ix
	ret

	extern	cpm_bdos_z80
