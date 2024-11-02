	.assume	adl = 1

	section	.text,"ax",@progbits
	.global	__port_out

; void _port_out(const uint24_t data)
__port_out:
	LD	IY, 0
	ADD	IY, SP
	LD	A, (IY + 3)
	LD	BC, (IY + 4)
	OUT	(BC), A
	RET
