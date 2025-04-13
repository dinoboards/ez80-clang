	.assume	adl=1
	section	.text, "ax", @progbits
	global	hbios_adl
	extern	hbios_z80

hbios_adl:
	push	ix
	push	iy
	CALL.sis hbios_z80 & $FFFF
	pop	iy
	pop	ix
	ret
