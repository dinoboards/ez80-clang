	.assume	adl=1

	section	.text, "ax", @progbits
	global	__hbios_cio_out

; uint8_t _hbios_cio_out(uint16_t ce);

__hbios_cio_out:
	pop	hl ; return address
	pop	de ; c and e
	ld	c, d
	push	de
	push	hl

	ld	b, 1
	jp	hbios_adl
