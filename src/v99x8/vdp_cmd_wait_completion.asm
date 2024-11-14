
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	.global	_vdp_cmd_wait_completion
_vdp_cmd_wait_completion:
	di
	; Set read register to 2
	ld	bc, VDP_ADDR

	ld	a, 2
	out	(BC), a
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	ld	a, 0x80|15				; measured on CPU running @25Mhz
	out	(BC), a

	DELAY_1_7US

_vdp_cmd_wait_completion_wait:
	in	a, (BC)
	rrca
	jr	c, _vdp_cmd_wait_completion_wait

	xor	a
	DELAY_1_7US
	out	(BC), a
	DELAY_1_7US					; DELAY and LD provde the ~2us required delay
	ld	a, 0x80|15				; measured on CPU running @25Mhz
	out	(BC), a

	ei
	ret
