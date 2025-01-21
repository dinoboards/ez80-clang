
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	.global	_vdp_out_reg_int16
; void vdp_out_reg_int16(uint16_t b)
_vdp_out_reg_int16:
	ld	iy, 0
	add	iy, sp
	ld	hl, (IY+3)
	ld	bc, (_VDP_IO_REGS)
	out	(bc), l
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	ld	a, 0					; measured on CPU running @25Mhz
	out	(bc), h
	ret
