
	.assume	adl = 1

	section	.text,"ax",@progbits

	include "src/v99x8/common.inc"

	section	.bss,"aw",@nobits

	.global	_vdp_cmdp_r36, _vdp_cmdp_r38, _vdp_cmdp_r40, _vdp_cmdp_r42, _vdp_cmdp_r44, _vdp_cmdp_r45, _vdp_cmdp_r46

_vdp_cmdp_r36:	DW	0

_vdp_cmdp_r38:	DW	0

_vdp_cmdp_r40:	DW	0

_vdp_cmdp_r42:	DW	0

_vdp_cmdp_r44:	DB	0

_vdp_cmdp_r45:	DB	0

_vdp_cmdp_r46:	DB	0

