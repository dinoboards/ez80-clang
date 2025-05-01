	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_usb_get_device_address

; extern uint8_t ez80_usb_get_device_address(uint8_t dev_index);
_ez80_usb_get_device_address:
	push	ix
	ld	ix, 0
	add	ix, sp

	LD	C, (ix+6)
	EZ80_USB_GET_DEV_TYP
	LD	A, D

	pop	ix
	ret
