	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_f_write

_cpm_f_write:
	call	__frameset0
	ld	de, (ix+6)		; must be within the current MBASE segment
	ld	c, F_WRITE
	call.sis cpm_bdos_z80 & 0xFFFF
	ld	l, h			; number of 128byte blocks written
	ld	h, a			; error code
	pop	ix
	ret

	extern	cpm_bdos_z80