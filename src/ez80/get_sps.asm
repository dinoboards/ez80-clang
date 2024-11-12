
	.assume	adl = 1

	section	.text,"ax",@progbits
	.global	__get_sps

; void* _get_sps()

__get_sps:
	LD	HL, 0
	ADD.S	HL, SP  ;//Is this safe - ius the definition of the upper byte perhaps undefined.
	LD	DE, (_cpm_mbase)
	ADD	HL, DE
	RET

	extern	_cpm_mbase
