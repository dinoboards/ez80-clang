	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_f_writerand

_cpm_f_writerand:
	call	__frameset0
	ld	de, (ix+6)		; must be within the current MBASE segment
	ld	c, F_WRITERAND
	call	cpm_bdos_adl
	ld	l, h			; hardware error code
	ld	h, a			; error code
	pop	ix
	ret

	extern	cpm_bdos_adl
