	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__port_out

; void _port_out(const uint24_t data)
__port_out:
	ld	iy, 0
	add	iy, sp
	ld	a, (IY+3)
	ld	bc, (IY+4)
	out	(BC), a
	ret
