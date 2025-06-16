	include	"src/cpm/cpm.inc"

	.assume	adl=0
	section	.text64k, "ax", @progbits
	.global	cpm_bdos_z80

cpm_bdos_z80:
	call	BDOS
	RET.L

