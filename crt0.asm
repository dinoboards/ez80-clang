
	.assume	adl = 0

	.extern	_main

	section .header, "ax", @progbits

	; nop

; .ifdef CPM_HEADER

	jp	__start
	; TODO ADD A HEADER HERE
; .endif

	section	.startup, "ax", @progbits
	global	__start
__start:
; Call main function
; ------------------
; Start of the C program called either as int main(void) or int main(int argc, char *argv[])
; - value returned will be in HL

; TODO - supply the command line arguments.
; TODO - zero out .bss section

	ld	hl, 0
	add	hl, sp
	ld	(__restore_sp_onexit+1), hl	;Save SPS stack
						; What about SPL stack
	call	crt0_init

	call.lil	__startadl ; 02 0018

__Exit:
	ld	(0x80),	hl			;Save exit value for CP/M 2.2
	push	hl				;Save return value
	call	crt0_exit
	pop	hl

	RET

	.assume	adl = 1

__startadl:
	ld	hl, 0
	push	hl				; argv
	push	hl				; argc
	call	_main				; int main(int argc, char *argv[])
	pop	bc				; kill argv
	pop	bc				; kill argc
	RET

	.assume	adl = 0

__restore_sp_onexit:
	ld	sp, 0		;Pick up entry sp
	ld	c, 12		;Get CPM version
	call	5
	cp	$30
	jp	c, 0		;Warm boot for CP/M < 3
	ld	a, l
	and	127
	ld	e, a
	ld	a, h		;Exit with d=$ff for error, or d=$00 for no error
	or	l
	jr	z, do_exit_v3
	ld	a, 255		;Indicate error
do_exit_v3:
	ld	d, a
	ld	c, 108
	call	5		;Report error
	rst	0

	SECTION	code_crt_init, "ax", @progbits

crt0_init:
	NOP

    	SECTION	code_crt_init_exit, "ax", @progbits
	RET

	SECTION	code_crt_exit, "ax", @progbits
crt0_exit:
	; Teardown code can go here
	SECTION	code_crt_exit_exit, "ax", @progbits
	ret


	SECTION code_crt_init, "ax", @progbits
	ld	c, 25
	call	5
	ld	(defltdsk), a


	SECTION code_crt_exit, "ax", @progbits

	ld	a, (defltdsk)        ;Restore default disc
	ld	e, a
	ld	c, 14
	call	5

	SECTION	bss_crt, "ax", @progbits
	global	defltdsk
defltdsk:       defb    0	;Default disc
