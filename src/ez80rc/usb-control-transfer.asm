	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_usb_control_transfer

; extern usb_error_t usb_control_transfer(const setup_packet_t *const cmd_packet, void *const buffer, uint8_t device_address, uint8_t max_packet_size);
;   IY -> cmd_packet
;   IX -> buffer
;   D -> device_address
;   E -> max_packet_size

_usb_control_transfer:
	push	ix
	ld	ix, 0
	add	ix, sp

	ld	iy, (ix+6)
	ld	d, (ix+12)
	ld	e, (ix+15)
	ld	ix, (ix+9)

	EZ80_USB_CONTROL_TRANSFER

	pop	ix
	ret
