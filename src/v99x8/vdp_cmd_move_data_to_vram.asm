

	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	section	.text, "ax", @progbits
	.assume	adl=1

	.global	_vdp_cmd_move_data_to_vram
; extern void vdp_cmd_move_data_to_vram(uint8_t first_byte, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t direction);

	; first_byte => iy + 3
	; x => iy + 6
	; y => iy + 9
	; width => iy + 12
	; height => iy + 15
	; direction => iy + 18

_vdp_cmd_move_data_to_vram:
	ld	iy, 0
	add	iy, sp

	SET_SLOW_IO_SPEED

	ld	bc, (_VDP_IO_ADDR)
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

	ld	a, CMD_HMMC				; submit command
	out	(bc), a

	ld	bc, (_VDP_IO_ADDR)			;
	ld	a, $80|44				; submit data to R#44 without auto increment
	out	(bc), a
	ld	a, $80|17				; to register 17
	out	(bc), a

	; SET STATUS REGISTER to #02
	ld	a, 2
	out	(BC), a
	ld	a, 0x80|15
	out	(BC), a

	RESTORE_IO_SPEED

	ret
