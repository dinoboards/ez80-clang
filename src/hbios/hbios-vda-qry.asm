	.assume	adl=1

	section	.text, "ax", @progbits
	global	_hbios_vda_qry

; typedef struct {
;   uint8_t video_mode;
;   uint8_t rows;
;   uint8_t columns;
;   uint8_t *font_map;
; } vda_info_t;
;
; int8_t hbios_vda_qry(uint8_t video_unit, uint8_t *new_font_map, vda_info_t* info);

_hbios_vda_qry:
	ld	iy, 0
	add	iy, sp

	ld	c, (iy+3)
	ld	hl, (iy+6)
	ld	iy, (iy+9)
	push	iy
	ld	b, $41
	call	hbios_adl
	pop	iy
	ld	(iy+0), c
	ld	(iy+1), d
	ld	(iy+2), e
	ld	(iy+3), l
	ld	(iy+4), h
	ex	af, af'
	ld	a, l
	or	h
	jr	z, .null_font_map
	ld	a, MB
	ld	(iy+5), a
	ex	af, af'
	ret

.null_font_map:
	xor	a
	ld	(iy+5), a
	ex	af, af'
	ret

