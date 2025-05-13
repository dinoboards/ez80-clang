	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_timers_ticks_set

; extern void ez80_timers_ticks_set(const uint24_t ticks);
_ez80_timers_ticks_set:
	ld	iy, 0
	add	iy, sp
	ld	hl, (iy+3)
	EZ80_UTIL_TMR_TICK_SET
	ret
