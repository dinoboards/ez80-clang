	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_timers_ticks_get

; extern uint24_t ez80_timers_ticks_get();
_ez80_timers_ticks_get:
	EZ80_UTIL_TMR_TICK_GET
	ret
