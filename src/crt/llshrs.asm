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
	.global	__llshrs
__llshrs:
; Suboptimal for large shift amounts
	push	af
	push	iy
	ld	iy, 0
	add	iy, sp
	ld	a, (iy+9)
	or	a, a
	jr	z, .finish
	push	de
	push	hl
.loop:
	sra	b
	.global	__llshrs_hijack_llshru
__llshrs_hijack_llshru:
	rr	c
	rr	(iy-1)
	rr	(iy-2)
	rr	(iy-3)
	rr	(iy-4)
	rr	(iy-5)
	rr	(iy-6)
	dec	a
	jr	nz, .loop
	pop	hl
	pop	de
	.global	__llshrs_finish
__llshrs_finish:
.finish:
	pop	iy
	pop	af
	ret
