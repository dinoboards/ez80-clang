	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_usbtrn_get_full_config_descriptor

; usb_error_t usbtrn_get_full_config_descriptor(uint8_t config_index, uint8_t device_address, uint8_t max_packet_size, uint8_t max_buffer_size, uint8_t *const buffer);
;   IX -> buffer
;   C -> config_index
;   D -> device address
;   E -> max packet size
;   HL -> max buffer size

_usbtrn_get_full_config_descriptor:
	push	ix
	ld	ix, 0
	add	ix, sp

	ld	c, (ix+6)
	ld	d, (ix+9)
	ld	e, (ix+12)
	ld	hl, (ix+15)
	ld	ix, (ix+18)

	EZ80_USBT_GET_FULL_DESC

	pop	ix
	ret
