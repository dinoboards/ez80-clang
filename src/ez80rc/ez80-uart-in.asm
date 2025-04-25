	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_uart_in

_ez80_uart_in:
	push	ix
	EZ80_UART_IN
	pop	ix
	ld	a, e
	ret
