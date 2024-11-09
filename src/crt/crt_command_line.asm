
; Command line parsing
	.assume	adl = 1

	.extern __call_main
	.extern ez80_cpy_mbhl_to_uhl
	section	.startup_adl, "ax", @progbits
	global	__push_cpm_cmdline_args

__push_cpm_cmdline_args:
	ld	hl, $80
	call	ez80_cpy_mbhl_to_uhl

	ld	a, (hl)
	ld	b, h
	and	a
	jr	z, argv_done
	ld	c, a
	add	hl, bc  				; now points to the end of the command line
	dec	c

; Push pointers to argv[n] onto the stack now
; We must start from the end
; Entry:  hl = end of arguments
;	   c = length of arguments
;	   b = 0
; Exit:	  bc = argc
;         hl = argv

argv_begin:
	ld	de, 0					; NULL pointer at end of array, just in case
	push	de

; Try to find the end of the arguments
argv_loop_1:
	ld	a, (hl)         			; Strip off trailing spaces
	cp	' '
	jr	nz, argv_loop_2
	ld	(hl), 0
	dec	hl
	dec	c
	jr	nz, argv_loop_1

; We've located the end of the last argument, try to find the start
argv_loop_2:
	ld	a, (hl)
	cp	' '
	jr	nz, argv_loop_3
	inc	hl              			; We're now on the first character of the argument
	inc	c

; TODO: Implement redirection here

	push	hl
	inc	b

empty_arg:
	dec	hl
	dec	c

; skip extra blanks
argv_zloop:
	ld	(hl),	0      				; Terminate the previous argument
	dec	hl         				; Last character of previous argument
	dec	c
	jr	z, argv_done
	ld	a, (hl)
	cp	' '
	jr	z, argv_zloop				; Skip over multiple spaces
	jr	argv_loop_2				; And do the next argument

argv_loop_3:
	dec	hl
	dec	c
	jr	nz, argv_loop_2

argv_done:
    ; We may still have an argument left (if it was at the start of the buffer)

argv_push_final_arg:
	ld	a, (hl)              			; Strip leading spaces
	cp	' '
	jr	nz,argv_push_final_arg2
	inc	hl
	jr	argv_push_final_arg

argv_push_final_arg2:
	pop	de                  			; Is it the same as the last argument we pushed?
	push	de
	ld	a, h
	sub	d
	jr	nz,argv_push_final_arg3
	ld	a, l
	sub	e
	jr	z, argv_done_2

argv_push_final_arg3:
	ld	a, (hl)
	and	a
	jr	z, argv_done_2
	push	hl
	inc	b

argv_done_2:
	ld	hl, commandline_argv0
	;name of program (NULL)
	push	hl
	inc	b
	ld	hl, 0
	add	hl, sp					; address of argv
	ld	c, b
	ld	b, 0

	push	hl					; argv
	push	bc					; argc

	JP	__call_main

commandline_argv0:		defb	0
