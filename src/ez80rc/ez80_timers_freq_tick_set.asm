	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_ez80_timers_freq_tick_set

; extern void ez80_timers_freq_tick_set();
_ez80_timers_freq_tick_set:
	call	__frameset0
	ld	c, (ix+6)
	EZ80_UTIL_TMR_FREQTICK_SET
	pop	ix
	ret
