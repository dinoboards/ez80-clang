	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_npf_max
_npf_max:
	push	ix
	ld	ix, 0
	add	ix, sp
	ld	de, (ix + 6)
	ld	hl, (ix + 9)
	ld	bc, -8388608
	push	de
	pop	iy
	add	iy, bc
	add	hl, bc
	lea	bc, iy + 0
	or	a, a
	sbc	hl, bc
	jr	c, BB0_2
	ld	de, (ix + 9)
BB0_2:
	ex	de, hl
	pop	ix
	ret
	section	.text,"ax",@progbits

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__Unwind_SjLj_Register
	.extern	__Unwind_SjLj_Unregister
