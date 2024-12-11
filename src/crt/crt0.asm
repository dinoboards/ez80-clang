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

	.assume	adl=0

	extern	_main
	extern	__push_cpm_cmdline_args

	section	.header_z80, "ax", @progbits

	; detect if running on eZ80
	ld	hl, $0040
	ld	ix, $0000

	lea	hl, ix+0

	ld	a, l
	or	a
	jr	z, __start
_z80:

	ld	c, 9			; print string
	ld	de, require_eZ80 & $FFFF
	call	5			; BDOS
	jp	0

require_eZ80:
	defm	"This program requires an eZ80 CPU."
	defb	13, 10, '$'

	section	.startup_z80, "ax", @progbits
	global	__start
	global	__call_main
	global	_exit
	global	_cpm_mbase

__start:
	ld	((__restore_sps_onexit+1)&$FFFF), sp	; Save SPS stack

	; SAVE DEFAULT DISC
	ld	c, 25
	call	5
	ld	(defltdsk & $FFFF), a

	call.lil	__startadl

	; Restore default disc
	push	hl
	ld	a, (defltdsk & $FFFF)
	ld	e, a
	ld	c, 14
	call	5
	pop	hl

	ld	(0x80), hl			;Save exit value for CP/M 2.2

__restore_sps_onexit:
	ld	sp, 0				;Pick up entry sp
	ld	c, 12				;Get CPM version
	call	5
	cp	$30
	jp	c, 0				;Warm boot for CP/M < 3
	ld	a, l
	and	127
	ld	e, a
	ld	a, h				;Exit with d=$ff for error, or d=$00 for no error
	or	l
	jr	z, do_exit_v3
	ld	a, 255				;Indicate error
do_exit_v3:

	ld	d, a
	ld	c, 108
	call	5				;Report error
	rst	0

	section	.startup_adl, "ax", @progbits
	.assume	adl=1

; Call main function
; ------------------
; Start of the C program called either as int main(void) or int main(int argc, char *argv[])
; - value returned will be in HL

__startadl:
	ld	(__restore_spl_onexit+1), sp	; Save SPL stack

	call	crt0_init
	jp	__push_cpm_cmdline_args

__call_main:
	call	_main				; int main(int argc, char *argv[])

__crt_exit:
	push	hl				; save return value
	call	crt0_exit
	pop	hl

__restore_spl_onexit:
	ld	sp, 0
	RET.L

_exit:
	pop	hl				; discard return address
	pop	hl				; retrieve return value
	jr	__crt_exit

	section	code_crt_init, "ax", @progbits

crt0_init:
	.extern	_length_of_bss
	.extern	_start_of_bss

.clear_bss:
	ld	hl, _start_of_bss
	ld	bc, _length_of_bss

	xor	a
	ld	d, a
.loop:
	ld	(HL), d
	inc	hl
	dec	bc
	ld	a, b
	or	c
	jr	nz, .loop

	ld	a, MB
	ld	(_cpm_mbase+2), a

	section	code_crt_init_exit, "ax", @progbits
	ret

	section	code_crt_exit, "ax", @progbits
crt0_exit:
	call	_run_atexit_funcs

	section	code_crt_exit_exit, "ax", @progbits
	ret

	section	bss_crt, "ax", @progbits
defltdsk:
	defb	0	;Default disc
_cpm_mbase:
	d24	0	;CP/M base address
