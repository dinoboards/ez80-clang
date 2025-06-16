;--------------------------------------------------------------
;
;	C RUNTIME FUNCTION
;	For the eZ80 Clang cross compiler
;
; This startup code is designed to run in a Z80-compatible environment,
; to start a COM executable under CP/M on an eZ80 CPU with firmware support
;
; It will transition execution to the _main function in eZ80's ADL mode.
; And upon return, execution will return to CP/M.
;
; Startup will exit with an error message, unless detection an eZ80 CPU
; is successful.
;
; As the code will be loaded via CP/M its maximum size is still limited to 64K.
;
;--------------------------------------------------------------

	.assume	adl=0

	extern	_main
	extern	__push_cpm_cmdline_args

	section	.header_z80, "ax", @progbits
	global	_get_memory_start
	global	_get_memory_end

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
	global	_CPM_SYS_FCB

__start:
	ld	((__restore_sps_onexit+1) & $FFFF), sp	; Save SPS stack

	call.lil	.bss_init

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
	ld	a, MB
	ld	(_cpm_mbase+2), a
	ld	(_CPM_SYS_FCB+2), a
	ld	a, $5C
	ld	(_CPM_SYS_FCB), a

	section	code_crt_init_exit, "ax", @progbits
	ret


_get_memory_start:
	ld	hl, (_cpm_mbase)
	ret

_get_memory_end:
	ld	hl,(_cpm_mbase)
	ld	bc, 0x10000
	add	hl, bc
	ret

	global	_get_memory_end

	.extern _on_chip_source
	.extern _start_of_on_chip
	.extern _length_of_on_chip
.bss_init:
.copy_text_on_chip:
	ld	bc, _length_of_on_chip
	ld	a, b
	or	c
	jr	z, .clear_bss
	ld	hl, _on_chip_source
	ld	de, _start_of_on_chip
	ldir

	.extern	_length_of_bss
	.extern	_start_of_bss
	.extern	_length_of_bss_on_chip
	.extern	_start_of_bss_on_chip

.clear_bss:
	ld	hl, _start_of_bss
	ld	bc, _length_of_bss
	call	.clear_section

	ld	hl, _start_of_bss_on_chip
	ld	bc, _length_of_bss_on_chip
	call	.clear_section
	ret.l

.clear_section:
	xor	a
	ld	d, a
	jr	.test_clear
.loop:
	ld	(HL), d
	inc	hl
	dec	bc

.test_clear:
	ld	a, b
	or	c
	jr	nz, .loop
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
_CPM_SYS_FCB:
	d24	0
