	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_term

_cpm_term:
	ld	c, P_TERMCPM
	ld	de, 0
	ld	hl, 0
	jp	cpm_bdos_adl	; ISSUE SPL is not correctly restored!

	extern	cpm_bdos_adl
