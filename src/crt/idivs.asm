	.assume adl=1

	section	.text,"ax",@progbits
	.global	__idivs

__idivs:
; I: UHL=dividend, UBC=divisor
; O: uhl=UHL/UBC

	push	de

	call	__idvrms

	pop	de
	ret


	extern	__idvrms

