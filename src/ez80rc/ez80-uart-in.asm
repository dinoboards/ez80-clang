	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_uart_in

_ez80_uart_in:
	EZ80_UART_IN
	ld	a, e
	ret
