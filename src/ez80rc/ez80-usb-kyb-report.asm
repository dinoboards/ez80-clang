	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_usb_kyb_report

_ez80_usb_kyb_report:
	push	ix
	ld	ix, 0
	add	ix, sp

	LD	HL, (ix+6)
	EZ80_USB_KYB_RPT
	pop	ix
	ret
