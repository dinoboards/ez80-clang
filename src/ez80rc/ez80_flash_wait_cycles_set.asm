	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_flash_wait_cycles_set

; extern uint8_t ez80_flash_wait_cycles_set(const uint8_t cycles);
_ez80_flash_wait_cycles_set:
	call	__frameset0
	ld	l, (ix+6)
	EZ80_UTIL_FLSHWS_SET
	ld	a, l
	pop	ix
	ret
