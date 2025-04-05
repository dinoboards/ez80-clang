	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_putchar
	extern	_cpm_c_write
	extern  __stdin

; int putchar(int character);
_putchar:
	pop	hl ; return address
	pop	de ; character

	ld	a, (__stdin)
	bit	0, a				; _stdin.mode & _IOTEXT_TRANSLATION
	jr	z, .skip

	ld	a, 10	; CR			; LF
	cp	e
	call	z, putchar_cr

.skip:
	push	de
	push	hl
	jp	_cpm_c_write

putchar_cr:
	push	hl
	push	de

	ld	e, 13				; CR
	push	de
	call	_cpm_c_write
	pop	de

	pop	de
	pop	hl
	ret
