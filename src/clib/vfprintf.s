	section	.text,"ax",@progbits
	.assume	adl = 1
	section	.text,"ax",@progbits
	.global	_vfprintf
_vfprintf:
	push	ix
	ld	ix, 0
	add	ix, sp
	ld	iy, (ix + 6)
	ld	de, (ix + 9)
	ld	bc, (ix + 12)
	ld	hl, _npf_fputc_std
	push	bc
	push	de
	push	iy
	push	hl
	call	_npf_vpprintf
	ld	sp, ix
	pop	ix
	ret
	section	.text,"ax",@progbits

	;ident	"clang version 15.0.0 (https://github.com/dinoboards/llvm-project.git 610487e5a2606567dc472eab6af41c09d7412837)"
	.extern	__Unwind_SjLj_Register
	.extern	__Unwind_SjLj_Unregister
	.extern	_npf_vpprintf
	.extern	_npf_fputc_std
