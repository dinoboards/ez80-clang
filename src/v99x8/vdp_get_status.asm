
	.assume	adl = 1

	section	.text,"ax",@progbits

	include "src/v99x8/common.inc"

	.global	_vdp_get_status
; uint8_t vdp_get_status(uint8_t r)
_vdp_get_status:
	LD	IY, 0
	ADD	IY, SP
	LD	L, (IY + 3)
	LD	BC, VDP_ADDR

	DI
	; SET READ REGISTER TO 15
	OUT	(BC), L
	DELAY_1_7US
	LD	A, 0x80 | 15
	OUT	(BC), A

	LD	HL, 0
	IN	L, (BC)					; READ STATUS

	DELAY_1_7US

	; RESTORE READ REGISTER TO DEFAULT OF 0
	XOR	A
	OUT	(BC), A
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	LD	A, 0x80 | 15				; measured on CPU running @25Mhz
	OUT	(BC), A
	EI
	LD	A, L
	RET
