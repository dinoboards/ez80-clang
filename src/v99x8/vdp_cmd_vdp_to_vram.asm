
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

; .macro	EZ80_DELAY
; 	RST.L	$18
; .endm

; .macro	DELAY_VDP  ; approx 1.7 us @25Mhz CPU
; 	EZ80_DELAY ; 5-6us seconds
; .endm

; CMD_HMMC	.EQU 0xF0
; CMD_HMMV	.EQU 0xC0
; VDP_REGS:	equ	$FF9B		; VDP register access (write only)
; VDP_ADDR:	equ	$FF99		; VDP address (write only)

	section	.text,"ax",@progbits
	.assume	adl = 1

	.global	_vdp_cmd_vdp_to_vram

; void vdp_cmd_vdp_to_vram(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t colour, uint8_t direction);

	; x => iy + 3
	; y => iy + 6
	; width => iy + 9
	; height => iy + 12
	; colour => iy + 15
	; direction => iy + 18

_Xvdp_cmd_vdp_to_vram:
	ld	iy, 0
	add	iy, sp

	ld	bc, VDP_ADDR
	ld	a, 36					; submit 36, with auto increment
	out	(bc), a
	DELAY_VDP
	ld	a, 0x80 | 17				; to register 17
	out	(bc), a

	ld	bc, VDP_REGS

	ld	hl, (iy + 3)				; load x
	DELAY_VDP
	out	(bc), l					; low byte into #R36
	DELAY_VDP
	out	(bc), h					; high byte into #R37

	ld	hl, (iy + 6)				; load y
	DELAY_VDP
	out	(bc), l					; low byte into #R38
	DELAY_VDP
	out	(bc), h					; high byte into #R39

	ld	hl, (iy + 9)				; load width
	DELAY_VDP
	out	(bc), l					; low byte into #R40
	DELAY_VDP
	out	(bc), h					; high byte into #R41

	ld	hl, (iy + 12)				; load height
	DELAY_VDP
	out	(bc), l					; low byte into #R42
	DELAY_VDP
	out	(bc), h					; high byte into #R43

	DELAY_VDP
	ld	a, (iy + 15)				; load colour
	out	(bc), a					; into #R44

	DELAY_VDP
	ld	a, (iy + 18)				; load direction
	out	(bc), a					; into #R45

	DELAY_VDP
	ld	a, CMD_HMMV				; submit command
	out	(bc), a

	ret