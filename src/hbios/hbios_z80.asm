	.assume	adl=0
	section	.text64k, "ax", @progbits
	global	hbios_z80

hbios_z80:
	CALL	$FFF0
	RET.L
