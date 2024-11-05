
	.assume	adl = 1

	section	.text,"ax",@progbits

	include "src/v99x8/common.inc"

	.global	_vdp_out_reg_int16
; void vdp_out_reg_int16(uint16_t b)
_vdp_out_reg_int16:
	LD	IY, 0
	ADD	IY, SP
	LD	HL, (IY + 3)
	LD	BC, VDP_REGS
	OUT	(BC), L
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	LD	A, 0					; measured on CPU running @25Mhz
	OUT	(BC), H
	RET
