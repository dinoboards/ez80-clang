	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_cpm_f_usernum
	.extern _errno

_cpm_f_usernum:
	call	__frameset0
	ld	e, (ix+6)
	ld	c, F_USERNUM
	call	cpm_bdos_adl
	ld	l, a
	pop	ix
	ret

	extern	cpm_bdos_adl
