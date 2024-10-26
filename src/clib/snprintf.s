	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_snprintf
_snprintf:
	push	ix
	ld	ix, 0
	add	ix, sp
	push	hl
	ld	iy, (ix + 6)
	ld	de, (ix + 9)
	ld	bc, (ix + 12)
	lea	hl, ix + 15
	ld	(ix - 3), hl
	ld	hl, (ix - 3)
	push	hl
	push	bc
	push	de
	push	iy
	call	_vsnprintf
	ld	sp, ix
	pop	ix
	ret
	section	.text,"ax",@progbits

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__Unwind_SjLj_Register
	.extern	__Unwind_SjLj_Unregister
	.extern	_vsnprintf
