	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_usbtrn_get_descriptor2

; extern usb_error_t usbtrn_get_descriptor2(device_descriptor_t *const buffer, const uint8_t device_address);
;   IX -> buffer
;   D -> device address

_usbtrn_get_descriptor2:
	push	ix
	ld	ix, 0
	add	ix, sp

	ld	d, (ix+9)
	ld	ix, (ix+6)

	EZ80_USBT_GET_DESC2

	pop	ix
	ret
