
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"


	.global	__vdp_reg_write
; void __vdp_reg_write(uint16_t rd)
__vdp_reg_write:
	ld	iy, 0
	add	iy, sp

	DI_AND_SAVE

	ld	hl, (IY+3)
	ld	bc, (_VDP_IO_ADDR)
	out	(BC), l
	ld	a, 0x80
	or	h

	DELAY_1_7US
	out	(BC), a

	RESTORE_EI
	ret

