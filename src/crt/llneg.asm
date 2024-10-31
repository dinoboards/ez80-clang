	.assume	adl=1

	section	.text,"ax",@progbits
	.global	__llneg
__llneg:
	or	a, a
	.global	__llneg_hijack_nc
__llneg_hijack_nc:
	ex	de, hl		; ude=UHL, uhl=UDE
	push	hl		; *spl=UDE
	sbc	hl, hl		; uhl=0
	sbc	hl, de		; uhl=-UHL
	ex	(sp), hl	; uhl=UDE, *spl=-UHL
	ex	de, hl		; ude=UDE, uhl=UHL
	ld	hl, 0		; uhl=0
	sbc	hl, de		; uhl=-UDE-(UHL!=0)
				;    =-UDEUHL>>24
	ex	de, hl		; ude=-UDEUHL>>24, uhl=UDE
	sbc	hl, hl		; uhl=-(UDEUHL!=0)
	or	a, a
	sbc	hl, bc		; uhl=-UBC-(UDEUHL!=0)
				;    =-UBCUDEUHL>>48
	ld	c, l
	ld	b, h		; bc=-BCUDEUHL>>48
	pop	hl		; bcudeuhl=-BCUDEUHL
	ret
