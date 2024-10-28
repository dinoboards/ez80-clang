
	.assume	adl = 0

	.extern	_main

	section .header_z80, "ax", @progbits

; .ifdef CPM_HEADER
	jp	__start & $FFFF
	; TODO ADD A HEADER HERE
; .endif

	section	.startup_z80, "ax", @progbits
	global	__start
__start:
	ld	((__restore_sps_onexit+1) & $FFFF), SP	; Save SPS stack

	; SAVE DEFAULT DISC
	ld	c, 25
	call	5
	ld	(defltdsk & $FFFF), a

	call.lil __startadl

	; XOR	A
	; LD	B,7
	; RST.L	$10

	; Restore default disc
	PUSH	HL
	ld	a, (defltdsk & $FFFF)
	ld	e, a
	ld	c, 14
	call	5
	POP	HL

	ld	(0x80),	hl			;Save exit value for CP/M 2.2

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
	.assume	adl = 1

; Call main function
; ------------------
; Start of the C program called either as int main(void) or int main(int argc, char *argv[])
; - value returned will be in HL

; TODO - supply the command line arguments.

__startadl:
	ld	(__restore_spl_onexit+1), SP	; Save SPL stack

	call	crt0_init

	ld	hl, 0
	push	hl				; argv
	push	hl				; argc
	call	_main				; int main(int argc, char *argv[])

__crt_exit:
	PUSH	HL				; save return value
	call	crt0_exit
	POP	HL

__restore_spl_onexit:
	ld	SP, 0
	RET.L

	.global	_exit
_exit:
	POP	HL				; discard return address
	POP	HL				; retrieve return value
	JR	__crt_exit

	SECTION	code_crt_init, "ax", @progbits

crt0_init:
	.extern _length_of_bss
	.extern _start_of_bss

.clear_bss:
	LD	HL, _start_of_bss
	LD	BC, _length_of_bss

	XOR	A
	LD	D, A
.loop:
	LD	(HL), D
	INC	HL
	DEC	BC
	LD 	A, B
	OR 	C
	JR 	NZ, .loop


    	SECTION	code_crt_init_exit, "ax", @progbits
	RET

	SECTION	code_crt_exit, "ax", @progbits
crt0_exit:
	CALL	_run_atexit_funcs

	SECTION	code_crt_exit_exit, "ax", @progbits
	ret

	SECTION	bss_crt, "ax", @progbits
	global	defltdsk
defltdsk:       defb    0	;Default disc
