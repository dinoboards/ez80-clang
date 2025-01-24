
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	section	.text, "ax", @progbits
	.assume	adl=1

	.global	_vdp_cmd_pset

; extern void vdp_cmd_pset(uint16_t x, uint16_t y, uint8_t colour, uint8_t operation);

	; x => iy + 3
	; y => iy + 6
	; colour => iy + 9
	; operation => iy + 12

_vdp_cmd_pset:
	ld	iy, 0
	add	iy, sp

	ld	bc, (_VDP_IO_ADDR)
	ld	a, 36					; submit 36, with auto increment
	out	(bc), a
	DELAY_VDP
	ld	a, 0x80|17				; to register 17
	out	(bc), a

	ld	bc, (_VDP_IO_REGS)

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

	DELAY_VDP
	xor	a
	out	(bc), a					; N/A #R40

	DELAY_VDP
	xor	a
	out	(bc), a					; N/A #R41

	DELAY_VDP
	xor	a
	out	(bc), a					; N/A #R42

	DELAY_VDP
	xor	a
	out	(bc), a					; N/A #R43

	DELAY_VDP
	ld	a, (iy+9)				; load colour
	out	(bc), a					; into #R44


	DELAY_VDP
	xor	a					; Memory select - not configurable yet
	out	(bc), a					; into #R45

	DELAY_VDP
	ld	a, (iy+12)				; load operation
	or	CMD_PSET
	out	(bc), a					; into #R46

	ret

