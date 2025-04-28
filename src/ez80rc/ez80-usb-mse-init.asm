	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_usb_mse_init

; uint8_t ez80_usb_mse_init(uint8_t dev_index);

_ez80_usb_mse_init:
	push	ix
	ld	ix, 0
	add	ix, sp

	LD	C, (ix+6)
	EZ80_USB_MSE_INIT

	pop	ix
	ret
