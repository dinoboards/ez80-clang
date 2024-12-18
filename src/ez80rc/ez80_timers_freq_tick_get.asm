	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_timers_freq_tick_get

; extern uint8_t ez80_timers_freq_tick_get();
_ez80_timers_freq_tick_get:
	EZ80_UTIL_TMR_FREQTICK_GET
	ld	a, c
	ret
