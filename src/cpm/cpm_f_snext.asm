	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_f_snext
	.extern _errno

_cpm_f_snext:
	call	__frameset0
	ld	de, (ix+6)		; must be within the current MBASE segment
	ld	c, F_SNEXT
	call.sis cpm_bdos_z80 & 0xFFFF
	ld	l, a
	ld	a, h
	ld	(_errno), a
	pop	ix
	ret

	extern	cpm_bdos_z80
