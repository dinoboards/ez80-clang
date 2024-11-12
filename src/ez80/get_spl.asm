
	.assume	adl = 1

	section	.text,"ax",@progbits
	.global	__get_spl

; void* _get_spl()

__get_spl:
	call	__frameset0
	PUSH	IX
	POP	HL
	POP	IX
	RET
