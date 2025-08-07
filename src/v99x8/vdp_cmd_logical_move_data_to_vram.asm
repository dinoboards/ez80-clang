

	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	section	.text, "ax", @progbits
	.assume	adl=1

	.global	_vdp_cmd_logical_move_data_to_vram

; void vdp_cmd_logical_move_data_to_vram(uint8_t first_byte,
;			    const uint16_t x,
;			    const uint16_t y,
;			    const uint16_t width,
;			    const uint16_t height,
;			    const uint8_t direction,
;			    const uint8_t operation)

	; first byte => iy + 3
	; x => iy + 6
	; y => iy + 9
	; width => iy + 12
	; height => iy + 15
	; direction => iy + 18
	; operation => iy + 21

_vdp_cmd_logical_move_data_to_vram:
	;backup interrupt
	ld	iy, 0
	add	iy, sp

	SET_SLOW_IO_SPEED

	ld	bc, (_VDP_IO_ADDR)			;
	ld	a, 36					; submit 36 with auto increment
	out	(bc), a
	ld	a, $80|17				; to register 17
	out	(bc), a

	ld	bc, (_VDP_IO_REGS)

	ld	hl, (iy+6)				; load x
	out	(bc), l					; low byte into #R36
	out	(bc), h					; high byte into #R37

	ld	hl, (iy+9)				; load y
	out	(bc), l					; low byte into #R38
	out	(bc), h					; high byte into #R39

	ld	hl, (iy+12)				; load width
	out	(bc), l					; low byte into #R40
	out	(bc), h					; high byte into #R41

	ld	hl, (iy+15)				; load height
	out	(bc), l					; low byte into #R42
	out	(bc), h					; high byte into #R43

	ld	a, (iy+3)				; load first byte
	out	(bc), a					; into #R44

	ld	a, (iy+18)				; load direction
	out	(bc), a					; into #R45

	ld	a, (iy+21)				; load operation
	or	CMD_LMMC				; submit command
	out	(bc), a					; into #R46

	ld	bc, (_VDP_IO_ADDR)			;
	ld	a, $80|44				; submit 44 without auto increment
	out	(bc), a
	ld	a, $80|17				; to register 17
	out	(bc), a

	RESTORE_IO_SPEED

	; SET STATUS REGISTER to #02
	ld	a, 2
	out	(BC), a
	ld	a, 0x80|15
	out	(BC), a

	ret
