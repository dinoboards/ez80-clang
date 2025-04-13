	.assume	adl=1

	section	.text, "ax", @progbits
	global	_hbios_vda_kst

; int8_t hbios_vda_kst(uint8_t video_unit);

_hbios_vda_kst:
	ld	iy, 0
	add	iy, sp

	ld	c, (iy+3)
	ld	b, $4C
	jp	hbios_adl

