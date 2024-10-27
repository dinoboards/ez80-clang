	.assume adl=1

	section	.text,"ax",@progbits
	.global	__ineg


__ineg:
	add	hl, de	; uhl=UHL+UDE
	ex	de, hl	; ude=UHL+UDE, uhl=UDE
	or	a, a
	sbc	hl, de	; uhl=UDE-(UHL+UDE)
			;    =UDE-UHL-UDE
			;    =-UHL
	ex	de, hl	; ude=-UHL, uhl=UHL+UDE
	add	hl, de	; uhl=UHL+UDE+-UHL
			;    =UDE
	ex	de, hl	; ude=UDE, uhl=-UHL
	ret

