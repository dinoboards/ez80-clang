
	.assume	adl = 1

	section	.text,"ax",@progbits

	include "src/v99x8/common.inc"

	.global _vdp_cmd_wait_completion
_vdp_cmd_wait_completion:
	DI
	; Set read register to 2
	LD	BC, VDP_ADDR

	LD	A, 2
	OUT	(BC), A
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	LD	A, 0x80 | 15				; measured on CPU running @25Mhz
	OUT	(BC), A

	DELAY_1_7US

_vdp_cmd_wait_completion_wait:
	IN	A, (BC)
	RRCA
	JR	C, _vdp_cmd_wait_completion_wait

	XOR	A
	DELAY_1_7US
	OUT	(BC), A
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	LD	A, 0x80 | 15				; measured on CPU running @25Mhz
	OUT	(BC), A

	EI
	RET
