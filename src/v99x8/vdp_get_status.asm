
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	.global	_vdp_get_status
; uint8_t vdp_get_status(uint8_t r)
_vdp_get_status:
	ld	iy, 0
	add	iy, sp
	ld	l, (IY+3)
	ld	bc, (_VDP_IO_ADDR)

	DI_AND_SAVE
	SET_SLOW_IO_SPEED

	; SET READ REGISTER TO 15
	out	(BC), l
	ld	a, 0x80|15
	out	(BC), a

	ld	hl, 0
	in	l, (BC)					; READ STATUS

	; RESTORE READ REGISTER TO DEFAULT OF 0
	xor	a
	out	(BC), a					; DELAY and LD provide the ~2us required delay
	ld	a, 0x80|15				; measured on CPU running @25Mhz
	out	(BC), a

	RESTORE_IO_SPEED
	RESTORE_EI

	ld	a, l
	ret
