
	.assume	adl = 1

	section	.text,"ax",@progbits

	include "src/v99x8/common.inc"

	.global	_vdp_cmd
_vdp_cmd:
	DI
	; SET INDIRECT REGISTER TO 36
	LD	A, 36
	DELAY_1_7US
	OUT	(BC), A
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	LD	A, 0x80 | 17				; measured on CPU running @25Mhz
	OUT	(BC), A

	LD	HL, _vdp_cmdp_r36
	LD	BC, VDP_REGS
	LD	A, 11
.outs:							; loop calibrated to have appro 2us
	PUSH	AF					; between rights
	POP	AF
	NOP						; spec seems to indicate we should have a period
							; of 8us after the 2nd byte is written
	LD	E, (HL)					; but we seem to get a way with 2us just fine???
	OUT	(BC), E
	INC	HL
	DEC	A
	JR	NZ, .outs

	LD	BC, VDP_ADDR
	XOR	A
	DELAY_1_7US
	OUT	(BC), A
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	LD	A, 0x80 | 15				; measured on CPU running @25Mhz
	OUT	(BC), A

	EI
	RET

	extern _vdp_cmdp_r36
