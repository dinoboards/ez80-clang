
	.assume	adl = 1

	section	.text,"ax",@progbits

	include "src/v99x8/common.inc"


	.global	__vdp_reg_write
; void __vdp_reg_write(uint16_t rd)
__vdp_reg_write:
	LD	IY, 0
	ADD	IY, SP
	LD	HL, (IY + 3)
	LD	BC, VDP_ADDR
	OUT	(BC), L
	LD	A, 0x80
	OR	H
	DELAY_1_7US
	OUT	(BC), A
	RET

