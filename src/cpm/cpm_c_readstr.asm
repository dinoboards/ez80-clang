	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_readstr

_cpm_c_readstr:
	call	__frameset0
	ld	de, (ix+6)		; must be within the current MBASE segment
	ld	c, C_READSTR
	call	cpm_bdos_adl
	push	de
	pop	hl
	pop	ix
	ret

	extern	cpm_bdos_adl
