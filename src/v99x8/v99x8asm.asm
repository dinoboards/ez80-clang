
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	section	.bss, "aw", @nobits

; 	.global	_vdp_cmdp_r36, _vdp_cmdp_r38, _vdp_cmdp_r40, _vdp_cmdp_r42, _vdp_cmdp_r44, _vdp_cmdp_r45, _vdp_cmdp_r46

; _vdp_cmdp_r36:
; 	dw	0

; _vdp_cmdp_r38:
; 	dw	0

; _vdp_cmdp_r40:
; 	dw	0

; _vdp_cmdp_r42:
; 	dw	0

; _vdp_cmdp_r44:
; 	db	0

; _vdp_cmdp_r45:
; 	db	0

; _vdp_cmdp_r46:
; 	db	0

	section	.data, "aw", @progbits

	.global	_VDP_IO_DATA, _VDP_IO_ADDR, _VDP_IO_STAT, _VDP_IO_PALT, _VDP_IO_REGS

; Default the VDP register values to the MSX default standard
; V9958 REGISTERS
_VDP_IO_DATA:
	dw	$FF98		; VDP data port (VRAM read/write)
_VDP_IO_ADDR:
	dw	$FF99		; VDP address (write only)
_VDP_IO_STAT:
	dw	$FF99		; VDP status (read only)
_VDP_IO_PALT:
	dw	$FF9A		; VDP palette latch (write only)
_VDP_IO_REGS:
	dw	$FF9B		; VDP register access (write only)
