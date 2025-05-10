
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	.global	_vdp_cmd
_vdp_cmd:
	DI_AND_SAVE
	SET_SLOW_IO_SPEED

	; SET INDIRECT REGISTER TO 36
	ld	a, 36
	out	(BC), a					; DELAY and LD provide the ~2us required delay
	ld	a, 0x80|17				; measured on CPU running @25Mhz
	out	(BC), a

	ld	hl, _vdp_cmdp_r36
	ld	bc, (_VDP_IO_REGS)
	ld	a, 11
.outs:							; spec seems to indicate we should have a period
							; of 8us after the 2nd byte is written
	ld	e, (HL)					; but we seem to get a way with 2us just fine???
	out	(BC), e
	inc	hl
	dec	a
	jr	nz, .outs

	ld	bc, (_VDP_IO_ADDR)
	xor	a
	out	(BC), a					; DELAY and LD provde the ~2us required delay
	ld	a, 0x80|15				; measured on CPU running @25Mhz
	out	(BC), a

	RESTORE_IO_SPEED
	RESTORE_EI
	ret

	extern	_vdp_cmdp_r36
