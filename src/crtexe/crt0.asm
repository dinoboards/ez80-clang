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
	extern	_main
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
	call	.clear_bss
	call	.clear_bss_z80

	ld	a, MB
	ld	(_cpm_mbase+2), a

	pop	hl				; discard return address

	call	_main

__crt_exit:
	push	hl				; save return value
	call	_run_atexit_funcs
	pop	hl

	jp	$200000

_exit:
	pop	hl				; discard return address
	pop	hl				; retrieve return value
	jr	__crt_exit


	.extern	_length_of_bss
	.extern	_start_of_bss

.clear_bss:
	ld	hl, _start_of_bss
	ld	bc, _length_of_bss
	jp	__clear_mem

	.extern	_length_of_bss_z80
	.extern	_start_of_bss_z80

.clear_bss_z80:
	ld	hl, _start_of_bss_z80
	ld	bc, _length_of_bss_z80
	jp	__clear_mem

__clear_mem:
	xor	a
	ld	d, a

.loop:
	ld	a, b
	or	c
	ret	z

	ld	(HL), d
	inc	hl
	dec	bc
	jr	.loop


	section	bss_crt, "ax", @progbits
	global	_cpm_mbase
_cpm_mbase:
	d24	0	;CP/M base address
