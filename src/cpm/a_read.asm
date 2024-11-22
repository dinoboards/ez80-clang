	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_a_read

_cpm_a_read:
	push	ix
	ld	c, A_READ
	call	cpm_bdos_adl
	pop	ix
	ret

	extern	cpm_bdos_adl
