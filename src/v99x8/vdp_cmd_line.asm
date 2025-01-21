

	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	section	.text, "ax", @progbits
	.assume	adl=1

	.global	_vdp_cmd_line


; extern void vdp_cmd_line(
;     uint16_t x, uint16_t y, uint16_t long_length, uint16_t short_length, uint8_t direction, uint8_t colour, uint8_t operation);
; x => iy + 3
; y => iy + 6
; long_length => iy+9
; short_length => iy+12
; direction => iy+15
; colour => iy+18
; operation => iy+21

_vdp_cmd_line:
	ld	iy, 0
	add	iy, sp

	ld	bc, VDP_ADDR				;
	ld	a, 36					; submit 36 with auto increment
	out	(bc), a
	DELAY_VDP
	ld	a, $80|17				; to register 17
	out	(bc), a

	ld	bc, VDP_REGS

	ld	hl, (iy+3)				; load x
	DELAY_VDP
	out	(bc), l					; low byte into #R36
	DELAY_VDP
	out	(bc), h					; high byte into #R37

	ld	hl, (iy+6)				; load y
	DELAY_VDP
	out	(bc), l					; low byte into #R38
	DELAY_VDP
	out	(bc), h					; high byte into #R39

	ld	hl, (iy+9)				; load long_length
	DELAY_VDP
	out	(bc), l					; low byte into #R40
	DELAY_VDP
	out	(bc), h					; high byte into #R41

	ld	hl, (iy+12)				; load short_length
	DELAY_VDP
	out	(bc), l					; low byte into #R42
	DELAY_VDP
	out	(bc), h					; high byte into #R43

	ld	hl, (iy+18)				; load colour
	DELAY_VDP
	out	(bc), l					; low byte into #R44

	DELAY_VDP
	ld	a, (iy+15)				; load direction
	out	(bc), a					; low byte into #R45

	DELAY_VDP
	ld	a, (iy+21)				; load operation
	or	CMD_LINE				; mask in command
	out	(bc), a					; low byte into #R46

	ret
