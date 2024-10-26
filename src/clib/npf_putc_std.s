	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_npf_putc_std
_npf_putc_std:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy + 3)
	ld	(iy + 3), hl
	jp	_putchar
	section	.text,"ax",@progbits

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__Unwind_SjLj_Register
	.extern	__Unwind_SjLj_Unregister
	.extern	_putchar
