

	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	section	.text, "ax", @progbits
	.assume	adl=1

	.global	_vdp_cmd_logical_move_cpu_to_vram

; void vdp_cmd_logical_move_cpu_to_vram(const uint8_t * const source,
;			    const uint16_t x,
;			    const uint16_t y,
;			    const uint16_t width,
;			    const uint16_t height,
;			    const uint8_t direction,
;			    const uint24_t length,
;			    const uint8_t operation)

	; source => iy + 3
	; x => iy + 6
	; y => iy + 9
	; width => iy + 12
	; height => iy + 15
	; direction => iy + 18
	; length => iy + 21
	; operation => iy + 24

_vdp_cmd_logical_move_cpu_to_vram:
	;backup interrupt
	ld	iy, 0
	add	iy, sp

	DI_AND_SAVE
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

	ld	hl, (iy+3)				; load source
	ld	a, (hl)					; load first byte
	inc	hl
	out	(bc), a					; into #R44

	ld	a, (iy+18)				; load direction
	out	(bc), a					; into #R45

	ld	a, (iy+24)				; load operation
	or	CMD_LMMC				; submit command
	out	(bc), a					; into #R46

	ld	de, (iy+21)				; load length

	ld	bc, (_VDP_IO_ADDR)			;
	ld	a, $80|44				; submit 44 without auto increment
	out	(bc), a
	ld	a, $80|17				; to register 17
	out	(bc), a

	; SET STATUS REGISTER to #02
	ld	a, 2
	out	(BC), a
	ld	a, 0x80|15
	out	(BC), a

	exx
	ld	bc, (_VDP_IO_ADDR)
	exx

	ld	bc, (_VDP_IO_REGS)

loop:
	exx
.wait:
	in	a, (bc)
	bit	7, a
	jr	z, .wait
	exx

	ld	a, (hl)					; load next byte
	inc	hl
	out	(bc), a					; submit to VDP

	dec	de
	ld	a, e
	or	d
	jr	nz, loop

	exx
	; RESTORE READ REGISTER TO DEFAULT OF 0
	xor	a
	out	(BC), a
	ld	a, 0x80|15
	out	(BC), a

	RESTORE_IO_SPEED
	RESTORE_EI

	ret
