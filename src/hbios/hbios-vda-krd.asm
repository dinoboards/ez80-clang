	.assume	adl=1

	section	.text, "ax", @progbits
	global	_hbios_vda_krd

; typedef struct {
;   uint8_t scan_code;
;   uint8_t key_state;
;   uint8_t key_code;
; } vda_keyrd_info_t;

; int8_t hbios_vda_krd(uint8_t video_unit, vda_keyrd_info_t* info);

_hbios_vda_krd:
	ld	iy, 0
	add	iy, sp

	ld	c, (iy+3)
	ld	iy, (iy+6)
	push	iy
	ld	b, $4E
	call	hbios_adl
	pop	iy
	ld	(iy+0), c
	ld	(iy+1), d
	ld	(iy+2), e
	ret

