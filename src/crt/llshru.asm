	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__llshru
__llshru:
; Suboptimal for large shift amounts
	push	af
	push	iy
	ld	iy, 0
	add	iy, sp
	ld	a, (iy + 9)
	or	a, a
	jp	z, __llshrs_finish
	push	de
	push	hl
	srl	b
	jp	__llshrs_hijack_llshru

	extern	__llshrs_finish
	extern	__llshrs_hijack_llshru
