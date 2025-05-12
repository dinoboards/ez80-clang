	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_usb_kyb_event

_usb_kyb_event:
	push	ix
	ld	ix, 0
	add	ix, sp

	LD	HL, (ix+6)
	EZ80_USB_KYB_EVNT
	pop	ix
	ret
