	include	"src/cpm/cpm.inc"
	include	"src/ez80rc/ez80-instr.inc"

	.assume	adl=1
	section	.text, "ax", @progbits
	.global	cpm_bdos_adl
	.global	cpm_bdos_adl_emulator
	.global	cpm_bdos_adl_emulator_size
	.extern cpm_bdos_z80

cpm_bdos_adl:
cpm_bdos_adl_native:
	; if running native z80 execution
	CALL.sis cpm_bdos_z80 & 0xFFFF
	RET

	; cpm_bdos_adl_emulator will be copied down and over native
	; if emulator execution is detected.
cpm_bdos_adl_emulator:
	; if running emulator z80 execution
	EZ80_EMULATOR_INVOKE cpm_bdos_z80
	RET
cpm_bdos_adl_emulator_end:

cpm_bdos_adl_emulator_size	equ	cpm_bdos_adl_emulator_end-cpm_bdos_adl_emulator
