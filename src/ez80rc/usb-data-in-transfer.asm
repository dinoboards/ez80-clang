	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_usb_data_in_transfer

; extern usb_error_t usb_data_in_transfer(uint8_t *buffer, uint16_t buffer_size, uint8_t device_address, uint8_t number, uint8_t max_packet_size, uint8_t *toggle);
;   IX -> buffer
;   HL -> buffer size
;   D -> device address
;   C -> interface number
;   E -> max_packet_size
;   IY -> toggle
;
_usb_data_in_transfer:
	push	ix
	ld	ix, 0
	add	ix, sp

	ld	hl, (ix+9)
	ld	d, (ix+12)
	ld	c, (ix+15)
	ld	e, (ix+18)
	ld	iy, (ix+21)
	ld	ix, (ix+6)

	EZ80_USB_DATA_IN_TRANSFER

	pop	ix
	ret
