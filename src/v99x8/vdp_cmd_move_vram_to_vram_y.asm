

	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	section	.text, "ax", @progbits
	.assume	adl=1

	.global	_vdp_cmd_move_vram_to_vram_y

; extern void vdp_cmd_move_vram_to_vram_y(uint16_t x, uint16_t from_y, uint16_t to_y, uint16_t height, uint8_t direction);

	; x => iy + 3
	; from_y => iy + 6
	; to_y => iy + 9
	; height => iy + 12
	; dir => iy + 15

_vdp_cmd_move_vram_to_vram_y:
	ld	iy, 0
	add	iy, sp

	DI_AND_SAVE
	SET_SLOW_IO_SPEED

	ld	bc, (_VDP_IO_ADDR)
	ld	a, 34					; submit 34, with auto increment
	out	(bc), a
	ld	a, 0x80|17				; to register 17
	out	(bc), a

	ld	bc, (_VDP_IO_REGS)

	ld	hl, (iy+6)				; load from_y
	out	(bc), l					; low byte into #R34
	out	(bc), h					; high byte into #R35

	ld	hl, (iy+3)				; load dx
	out	(bc), l					; low byte into #R36
	out	(bc), h					; high byte into #R37

	ld	hl, (iy+9)				; load to_y
	out	(bc), l					; low byte into #R38
	out	(bc), h					; high byte into #R39

	xor	a
	out	(bc), a					; N/A #R40
	xor	a
	out	(bc), a					; N/A #R41

	ld	hl, (iy+12)				; load height
	out	(bc), l					; low byte into #R42
	out	(bc), h					; high byte into #R43

	xor	a
	out	(bc), a					; N/A #R44

	ld	hl, (iy+15)				; load direction
	out	(bc), l					; low byte into #R45

	ld	a, CMD_HMMM
	out	(bc), a					; into #R46

	RESTORE_IO_SPEED
	RESTORE_EI

	ret
