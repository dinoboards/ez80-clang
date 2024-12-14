
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	.global	_vdp_cmd
_vdp_cmd:
	di
	; SET INDIRECT REGISTER TO 36
	ld	a, 36
	DELAY_1_7US
	out	(BC), a
	DELAY_1_7US					; DELAY and LD provide the ~2us required delay
	ld	a, 0x80|17				; measured on CPU running @25Mhz
	out	(BC), a

	ld	hl, _vdp_cmdp_r36
	ld	bc, VDP_REGS
	ld	a, 11
.outs:							; loop calibrated to have appro 2us
	push	af					; between rights
	pop	af
	nop						; spec seems to indicate we should have a period
							; of 8us after the 2nd byte is written
	ld	e, (HL)					; but we seem to get a way with 2us just fine???
	out	(BC), e
	DELAY_1_7US
	inc	hl
	dec	a
	jr	nz, .outs

	ld	bc, VDP_ADDR
	xor	a
	DELAY_1_7US
	out	(BC), a
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	ld	a, 0x80|15				; measured on CPU running @25Mhz
	out	(BC), a

	ei
	ret

	extern	_vdp_cmdp_r36
