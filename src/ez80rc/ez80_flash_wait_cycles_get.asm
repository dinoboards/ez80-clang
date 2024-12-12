	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_flash_wait_cycles_get

; extern uint8_t ez80_flash_wait_cycles_get(void);
_ez80_flash_wait_cycles_get:
	push	ix
	EZ80_UTIL_FLSHWS_GET
	ld	a, l
	pop	ix
	ret
