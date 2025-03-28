;--------------------------------------------------------------
; Custom startup code for 'EXE' programs
; Expected to be loaded via EXE.COM on CP/M
;
;--------------------------------------------------------------

	.assume	adl=1
	extern	_main
	section	.header_adl, "ax", @progbits

application_load_addr:
	jp	__start

; TODO - add a header to the EXE file
	ds	16		; reserve 16 bytes for the header

	section	.startup_adl, "ax", @progbits
	global	__start
	global	_exit
	global	__get_sps

__start:
	call	.init_text_on_chip
	call	.clear_bss_on_chip
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

	jp	application_load_addr - $400

_exit:
	pop	hl				; discard return address
	pop	hl				; retrieve return value
	jr	__crt_exit


.init_text_on_chip:
	.extern	_on_chip_source
	.extern	_start_of_on_chip
	.extern	_length_of_on_chip
	ld	bc, _length_of_on_chip
	ld	a, b
	or	c
	ret	z
	ld	hl, _on_chip_source
	ld	de, _start_of_on_chip
	ldir
	ret

.clear_bss_on_chip:
	.extern	_length_of_bss_on_chip
	.extern	_start_of_bss_on_chip

	ld	de, _start_of_bss_on_chip
	ld	hl, _length_of_bss_on_chip
	jr	__clear_mem

.clear_bss:
	.extern	_length_of_bss
	.extern	_start_of_bss

	ld	de, _start_of_bss
	ld	hl, _length_of_bss
	jr	__clear_mem

.clear_bss_z80:
	.extern	_length_of_bss_z80
	.extern	_start_of_bss_z80

	ld	de, _start_of_bss_z80
	ld	hl, _length_of_bss_z80
	; jp	__clear_mem

__clear_mem:
	xor	a
	ld	bc, 0
	jr	.loop_test
.loop:
	ld	(de), a
	inc	de
	dec	hl

.loop_test:
	sbc	hl, bc
	jr	nz, .loop
	ret


	section	bss_crt, "ax", @progbits
	global	_cpm_mbase
_cpm_mbase:
	d24	0	;CP/M base address
