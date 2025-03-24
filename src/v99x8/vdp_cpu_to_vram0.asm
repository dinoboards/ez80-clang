	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	.global	_vdp_cpu_to_vram0

; fast hdmi version

; void vdp_cpu_to_vram(const uint8_t* const source, uint16_t length)

_vdp_cpu_to_vram0:
	ld	iy, 0
	add	iy, sp
	; iy + 3 -> source
	; iy + 6 -> length

	; Write to VDP_ADDR:
	;  0000 0 <A16..A14> 	of vdp_address
	;  1000 1110 		select register 14
	;  <A7..A0> 		of vdp_address
	;  01 <A13..A8> 	of vdp_address to enable write mode

	xor	a

	ld	bc, (_VDP_IO_ADDR)
	DELAY_1_7US
	out	(bc), a			; value for reg 14 (B16..B14)
	ld	a, $80+14		; VDP register 14
	DELAY_1_7US
	out	(bc), a

	xor	a
	DELAY_1_7US
	out	(bc), a			; submit bits 0 to 7

	ld	a, %01000000		; enable write mode
	DELAY_1_7US
	out	(bc), a			; submit bits 8 to 13

	ld	de, (iy+6)		; length
	ld	hl, (iy+3)		; source
	ld	bc, (_VDP_IO_DATA)

loop:
	ld	a, (hl)
	inc	hl
	DELAY_1_7US
	out	(bc), a
	dec	de
	ld	a, e		; warning only 16bit counter
	or	d
	jr	nz, loop

	ret

