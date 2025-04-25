	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_uart_out

_ez80_uart_out:
	ld	iy, 0
	add	iy, sp

	LD	E, (iy+3)
	EZ80_UART_OUT
	ret
