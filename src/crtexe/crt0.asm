;--------------------------------------------------------------
;
;	C RUNTIME FUNCTION
;	For the eZ80 Clang cross compiler
;
;  Original file source: https://github.com/CE-Programming/toolchain
;  License: https://github.com/CE-Programming/toolchain?tab=LGPL-3.0-1-ov-file
;
; Modified to comply with GNU AS assembler (ez80-none-elf-as) syntax
;
;--------------------------------------------------------------

	.assume	adl=1
	extern _main
	section	.header_adl, "ax", @progbits

; .ifdef CPM_HEADER
	jp	__start
	; TODO ADD A HEADER HERE
; .endif

	section	.startup_adl, "ax", @progbits
	global	__start
	global	_exit
	global	__get_sps

__start:
	jp	_main

_exit	equ	0x200000


	; TODO also move to there own file
__get_sps:
	; LD	A,-1
	; LD	HL, -1
	RET
