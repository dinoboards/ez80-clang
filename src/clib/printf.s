	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_printf
_printf:
	ld	iy, 0
	add	iy, sp
	push	hl
	ld	hl, (iy + 3)
	lea	de, iy + 6
	ld	(iy - 3), de
	ld	de, (iy - 3)
	push	de
	push	hl
	call	_vprintf
	ld	iy, 9
	add	iy, sp
	ld	sp, iy
	ret
	section	.text,"ax",@progbits

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__Unwind_SjLj_Register
	.extern	__Unwind_SjLj_Unregister
	.extern	_vprintf
