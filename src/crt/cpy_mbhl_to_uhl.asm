	.assume adl=1

	section	.text,"ax",@progbits
	.global	ez80_cpy_mbhl_to_uhl

ez80_cpy_mbhl_to_uhl:
	PUSH	IX
	PUSH	AF
	LD	IX, 0
	ADD	IX, SP
	PUSH	HL
	LD	A, MB
	LD	(IX-1), A
	POP	HL
	POP	AF
	POP	IX
	RET
