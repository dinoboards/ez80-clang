	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_f_dmaoff

_cpm_f_dmaoff:
	call	__frameset0
	ld	de, (ix+6)		; must be within the current MBASE segment
	ld	c, F_DMAOFF
	call	cpm_bdos_adl
	pop	ix
	ret

	extern	cpm_bdos_adl
