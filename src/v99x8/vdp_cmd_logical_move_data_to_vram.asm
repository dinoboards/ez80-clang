

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
;			    const uint24_t length,
;			    const uint8_t operation)

	; first byte => iy + 3
	; x => iy + 6
	; y => iy + 9
	; width => iy + 12
	; height => iy + 15
	; direction => iy + 18
	; length => iy + 21
	; operation => iy + 24

_vdp_cmd_logical_move_data_to_vram:
	;backup interrupt
	ld	iy, 0
	add	iy, sp

	DI_AND_SAVE

	ld	bc, (_VDP_IO_ADDR)			;
	ld	a, 36					; submit 36 with auto increment
	out	(bc), a
	DELAY_VDP
	ld	a, $80|17				; to register 17
	out	(bc), a

	ld	bc, (_VDP_IO_REGS)

	ld	hl, (iy+6)				; load x
	DELAY_VDP
	out	(bc), l					; low byte into #R36
	DELAY_VDP
	out	(bc), h					; high byte into #R37

	ld	hl, (iy+9)				; load y
	DELAY_VDP
	out	(bc), l					; low byte into #R38
	DELAY_VDP
	out	(bc), h					; high byte into #R39

	ld	hl, (iy+12)				; load width
	DELAY_VDP
	out	(bc), l					; low byte into #R40
	DELAY_VDP
	out	(bc), h					; high byte into #R41

	ld	hl, (iy+15)				; load height
	DELAY_VDP
	out	(bc), l					; low byte into #R42
	DELAY_VDP
	out	(bc), h					; high byte into #R43

	DELAY_VDP
	ld	a, (iy+3)				; load first byte
	out	(bc), a					; into #R44

	DELAY_VDP
	ld	a, (iy+18)				; load direction
	out	(bc), a					; into #R45

	DELAY_VDP
	ld	a, (iy+24)				; load operation
	or	CMD_LMMC				; submit command
	out	(bc), a					; into #R46

	ld	de, (iy+21)				; load length

	ld	bc, (_VDP_IO_ADDR)			;
	ld	a, $80|44				; submit 44 without auto increment
	out	(bc), a
	DELAY_VDP
	ld	a, $80|17				; to register 17
	out	(bc), a

	RESTORE_EI

	ret
