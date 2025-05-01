	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_usb_mse_state

_ez80_usb_mse_state:
	push	ix
	ld	ix, 0
	add	ix, sp

	LD	C, 1		; request current instantaneous report
	LD	HL, (ix+6)
	EZ80_USB_MSE_READ
	pop	ix
	ret
