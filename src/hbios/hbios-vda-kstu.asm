	.assume	adl=1

	section	.text, "ax", @progbits
	global	_hbios_vda_kstu

;typedef struct {
;   uint8_t bModifierKeys;
;   uint8_t bReserved;
;   uint8_t keyCode[6];
; } usb_keyboard_report_t;
;
; int8_t hbios_vda_kstu(uint8_t video_unit, usb_keyboard_report_t* usb_keyboard_report);

_hbios_vda_kstu:
	ld	iy, 0
	add	iy, sp

	ld	c, (iy+3)
	ld	iy, (iy+6)
	push	iy

	ld	b, $4C
	call	hbios_adl
	pop	iy
	ex	af, af'
	ld	(iy), a
	ex	af, af'
	ld	(iy+2), b
	ld	(iy+3), c
	ld	(iy+4), e
	ld	(iy+5), d
	ld	(iy+6), l
	ld	(iy+7), h
	ret


