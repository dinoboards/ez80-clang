;--------------------------------------------------------------
;
;	C RUNTIME FUNCTION
;	For the eZ80 Clang cross compiler
;
;  Original file source: https://github.com/CE-Programming/toolchain
;  License: https://github.com/CE-Programming/toolchain?tab=LGPL-3.0-1-ov-file
;
; Modified to comply with GNU AS assembler (ez80-none-elf-as) syntax
;
;--------------------------------------------------------------

	.assume	adl=1

	section	.text, "ax", @progbits

	.global	__ishl
	.global	__sshl

__ishl:
__sshl:
; CC: if 0<=C<8:   23*r(PC)+3*r(SPL)+4+(C&1==0)+(C&2!=0)*(1*r(PC)-1)+(C&4!=0)*(3*r(PC)-1)
;     if 8<=C<16:  30*r(PC)+3*r(SPL)+5+(C&1==0)+(C&2!=0)*(1*r(PC)-1)+(C&4!=0)*(3*r(PC)-1)
;     if 16<=C<24: 35*r(PC)+3*r(SPL)+5+(C&1==0)+(C&2!=0)*(1*r(PC)-1)+(C&4!=0)*(3*r(PC)-1)
	bit	0, c
	jr	z, .bit0
	add	hl, hl
.bit0:
	bit	1, c
	jr	z, .bit1
	add	hl, hl
	add	hl, hl
.bit1:
	bit	2, c
	jr	z, .bit2
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
.bit2:
	bit	3, c
	jr	nz, __ishl_8
	bit	4, c
	ret	z
__ishl_16:
	ld	h, l
	ld	l, 0
__ishl_8:
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	add	hl, hl
	ret
