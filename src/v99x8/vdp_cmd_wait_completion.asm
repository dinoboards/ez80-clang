
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	.global	_vdp_cmd_wait_completion
_vdp_cmd_wait_completion:
	di
	; Set read register to 2
	ld	bc, (_VDP_IO_ADDR)

	ld	a, 2
	out	(bc), a
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	ld	a, 0x80|15				; measured on CPU running @25Mhz
	out	(bc), a

	DELAY_1_7US


	ld	hl, 0
_vdp_cmd_wait_completion_wait:
	in	a, (BC)
	rrca
	jr	nc, _vdp_cmd_wait_completion_ready
	dec	hl
	ld	a, l
	or	h
	jr	nz, _vdp_cmd_wait_completion_wait

;  If here, command has not completed - probably waiting for additional data
; can we issue a reset command here??


_vdp_cmd_wait_completion_ready:
	xor	a
	DELAY_1_7US
	out	(BC), a
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	ld	a, 0x80|15				; measured on CPU running @25Mhz
	out	(BC), a

	ei
	ret
