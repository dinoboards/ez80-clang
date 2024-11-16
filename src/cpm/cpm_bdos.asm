	include	"src/cpm/cpm.inc"

	.assume	adl=0
	section	.startup_z80, "ax", @progbits
	.global	cpm_bdos_z80
cpm_bdos_z80:
	call	BDOS
	RET.L
