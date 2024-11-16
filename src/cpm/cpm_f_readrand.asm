	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_f_readrand

_cpm_f_readrand:
	call	__frameset0
	ld	de, (ix+6)		; must be within the current MBASE segment
	ld	c, F_READRAND
	call.sis cpm_bdos_z80 & 0xFFFF
	ld	l, h			; number of 128byte blocks read
	ld	h, a			; error code
	pop	ix
	ret

	extern	cpm_bdos_z80
