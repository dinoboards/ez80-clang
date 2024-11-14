
	.assume	adl=1

	section	.text, "ax", @progbits
	.global	__get_sps

; void* _get_sps()

__get_sps:
	ld	hl, 0
	ADD.S	hl, sp  ;//Is this safe - ius the definition of the upper byte perhaps undefined.
	ld	de, (_cpm_mbase)
	add	hl, de
	ret

	extern	_cpm_mbase
