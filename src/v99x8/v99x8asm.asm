
	.assume	adl=1

	section	.text, "ax", @progbits

	include	"src/v99x8/common.inc"

	section	.bss, "aw", @nobits

	.global	_vdp_cmdp_r36, _vdp_cmdp_r38, _vdp_cmdp_r40, _vdp_cmdp_r42, _vdp_cmdp_r44, _vdp_cmdp_r45, _vdp_cmdp_r46

_vdp_cmdp_r36:
	dw	0

_vdp_cmdp_r38:
	dw	0

_vdp_cmdp_r40:
	dw	0

_vdp_cmdp_r42:
	dw	0

_vdp_cmdp_r44:
	db	0

_vdp_cmdp_r45:
	db	0

_vdp_cmdp_r46:
	db	0

