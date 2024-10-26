	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_npf_putc_cnt
_npf_putc_cnt:
	push	ix
	ld	ix, 0
	add	ix, sp
	ld	bc, (ix + 6)
	ld	iy, (ix + 9)
	ld	de, (iy + 6)
	inc	de
	ld	(iy + 6), de
	ld	hl, (iy)
	ld	de, (iy + 3)
	ld	(ix + 6), bc
	ld	(ix + 9), de
	pop	ix
	jp	(hl)
	section	.text,"ax",@progbits

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__Unwind_SjLj_Register
	.extern	__Unwind_SjLj_Unregister
