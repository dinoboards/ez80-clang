	include	"src/cpm/cpm.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_bdos

; uint8_t bdos(uint16_t bc, uint16_t de);

_bdos:
	call	__frameset0
	ld	bc, (ix+6)
	ld	de, (ix+9)
	call	cpm_bdos_adl
	pop	ix
	ret

	extern	__frameset0
	extern	cpm_bdos_adl
