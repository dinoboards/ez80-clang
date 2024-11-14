	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	cpm_bdos

cpm_bdos:
	push	ix

	CALL.SIS	cpm_bdos_z80&0xFFFF

	pop	ix
	ret

	.assume	adl=0
	section	.startup_z80, "ax", @progbits
cpm_bdos_z80:
	call	BDOS
	RET.L
