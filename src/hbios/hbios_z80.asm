	.assume	adl=0
	section	.startup_z80, "ax", @progbits
	.global	hbios_z80
hbios_z80:
	CALL	$FFF0
	RET.L
