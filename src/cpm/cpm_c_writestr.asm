	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_c_writestr

_cpm_c_writestr:
	call	__frameset0
	ld	de, (ix+6)		; must be within the current MBASE segment
	ld	c, C_WRITESTR
	call.sis cpm_bdos_z80 & 0xFFFF
	pop	ix
	ret

	extern	cpm_bdos_z80
