	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_usb_kyb_report

_ez80_usb_kyb_report:
	ld	iy, 0
	add	iy, sp

	LD	HL, (iy+3)
	push	ix
	EZ80_USB_KYB_RPT
	pop	ix
	ret
