
	.assume	adl = 1

	section	.text,"ax",@progbits

	include "src/v99x8/common.inc"

	section	.bss,"aw",@nobits

	.global	_vdp_cmdp_from_x, _vdp_cmdp_from_y, _vdp_cmdp_color, _vdp_cmdp_operation, _vdp_cmdp_long_side, _vdp_cmdp_short_side, _vdp_cmdp_dir
	.global	_vdp_cmdp_r36, _vdp_cmdp_r38, _vdp_cmdp_r40, _vdp_cmdp_r42, _vdp_cmdp_r44, _vdp_cmdp_r45, _vdp_cmdp_r46
	.global	_vdp_cmdp_dx, _vdp_cmdp_dy, _vdp_cmdp_nx, _vdp_cmdp_ny

_vdp_cmdp_r36:
_vdp_cmdp_dx:
_vdp_cmdp_from_x:	DW	0

_vdp_cmdp_r38:
_vdp_cmdp_dy:
_vdp_cmdp_from_y:	DW	0

_vdp_cmdp_r40:
_vdp_cmdp_nx:
_vdp_cmdp_long_side:	DW	0

_vdp_vmdp_r42:
_vdp_cmdp_ny:
_vdp_cmdp_short_side:	DW	0

_vdp_cmdp_r44:
_vdp_cmdp_color:	DB	0

_vdp_cmdp_r45:
_vdp_cmdp_dir:		DB	0

_vdp_cmdp_r46:
_vdp_cmdp_operation:	DB	0

