	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_npf_bufputc
_npf_bufputc:
	push	ix
	ld	ix, 0
	add	ix, sp
	ld	iy, (ix + 9)
	ld	de, (iy + 6)
	ld	bc, (iy + 3)
	push	de
	pop	hl
	sbc	hl, bc
	jr	nc, BB0_2
	ld	a, (ix + 6)
	ld	hl, (iy)
	push	de
	pop	bc
	inc	bc
	ld	(iy + 6), bc
	add	hl, de
	ld	(hl), a
BB0_2:
	pop	ix
	ret
	section	.text,"ax",@progbits

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__Unwind_SjLj_Register
	.extern	__Unwind_SjLj_Unregister
