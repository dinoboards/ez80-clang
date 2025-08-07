

	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	section	.text, "ax", @progbits
	.assume	adl=1

; bool vdp_cmd_send_byte(uint8_t next_byte);
	.global	_vdp_cmd_send_byte

_vdp_cmd_send_byte:
	ld	iy, 0
	add	iy, sp

.if VDP_V9958=1
	IN0	A, (CS2_BMC)					; SAVE CURRENT CS2 (EXT IO) TIMING
	PUSH	AF

	LD	A, BMX_BM_Z80 | BMX_AD_SEPARATE | BMX_BC_15	; SET I/O TIMING TO 15BC
	OUT0	(CS2_BMC), A
.endif

	; ensure TR
	ld	bc, (_VDP_IO_ADDR)
	ld	de, 0
wait:
	in	a, (bc)
	bit	7, a
	jr	nz, ready

	dec	de
	ld	a, e
	or	d
	jr	nz, wait

timeout:
.if VDP_V9958=1
	POP	AF
	OUT0	(CS2_BMC), A
.endif
	xor	a
	ret

ready:
	ld	a, (iy+3)
	ld	bc, (_VDP_IO_REGS)
	out	(bc), a

.if VDP_V9958=1
	POP	AF
	OUT0	(CS2_BMC), A
.endif

	LD	A, 1
	RET

