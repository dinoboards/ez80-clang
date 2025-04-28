	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_usb_get_device_type

; usb_device_t usb_get_device_type(uint8_t dev_index);
; Inputs
;  C -> Device Index
;
; Outputs
;   A -> device_type (-1 is no device at dev_index)
_usb_get_device_type:
	push	ix
	ld	ix, 0
	add	ix, sp

	LD	C, (ix+6)
	EZ80_USB_GET_DEV_TYP

	pop	ix
	ret
