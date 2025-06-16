	include	"src/cpm/cpm.inc"

	.assume	adl=1
	section	.text, "ax", @progbits
	.global	cpm_bdos_adl
	.extern	cpm_bdos_z80

cpm_bdos_adl:
	CALL.sis cpm_bdos_z80 & 0xFFFF
	RET
