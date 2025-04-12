	include	"src/cpm/cpm.inc"

	.assume	adl=1
	section	.text, "ax", @progbits
	global	hbios_adl
	extern hbios_z80

hbios_adl:
	CALL.sis hbios_z80 & 0xFFFF
	RET
