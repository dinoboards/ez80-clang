
	.assume	adl = 1

	section	.text,"ax",@progbits
	.global	_get_address_in_base

; uint24_t _get_address_in_base(const uint16_t a)

_get_address_in_base:
	call	__frameset0
	LD	A, MB
	ld	(ix + 8), A
	ld	hl, (ix + 6)
	POP	IX
	RET
