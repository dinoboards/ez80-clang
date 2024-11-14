
	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_get_address_in_base

; uint24_t _get_address_in_base(const uint16_t a)

_get_address_in_base:
	call	__frameset0
	ld	a, MB
	ld	(ix+8), a
	ld	hl, (ix+6)
	pop	ix
	ret
