	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_f_sfirst
	.extern _errno

_cpm_f_sfirst:
	call	__frameset0
	ld	de, (ix+6)		; must be within the current MBASE segment
	ld	c, F_SFIRST
	call	cpm_bdos_adl
	ld	l, a
	ld	a, h
	ld	(_errno), a
	pop	ix
	ret

	extern	cpm_bdos_adl
