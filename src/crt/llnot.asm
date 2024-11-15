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
	.global	__llnot
__llnot:
	push	hl		; *spl=UHL
	add	hl, de		; uhl=UHL+UDE
	ex	de, hl		; ude=UHL+UDE, uhl=UDE
	scf
	sbc	hl, de		; uhl=UDE-(UHL+UDE)-1
				;    =UDE-UHL-UDE-1
				;    =-UHL-1
				;    =~UHL
	ex	(sp), hl	; uhl=UHL, *spl=~UHL
	scf
	sbc	hl, de		; uhl=UHL-(UHL+UDE)-1
				;    =UHL-UHL-UDE-1
				;    =-UDE-1
				;    =~UDE
	ex	de, hl		; ude=~UDE, uhl=UHL+UDE
	sbc	hl, hl		; uhl=-some_bool
	ccf			; cf=!some_bool
	sbc	hl, bc		; uhl=-some_bool-UBC-!some_bool
				;    =-UBC-(some_bool+!some_bool)
				;    =-UBC-1
				;    =~UBC
	ld	c, l
	ld	b, h		; bc=~BC
	pop	hl		; uhl=~UHL
	ret
