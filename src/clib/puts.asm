; Updated by Paul Cawte 13/06/2023
;
; Modifed to output CR/LF rather than just LF at end of line
; Detects NULL pointer (11/07/2023) - and just prints newline

	.assume	adl=1

	section	.text,"ax",@progbits
	.global	_puts
_puts:
	pop	de
	ex	(sp), hl
	push	de
	or 	a, a
	ld	de, 0
	sbc	hl, de
	jr	nz, .loop
	ld	hl, ___null_literal_str
.loop:
	call	puts_loop
	ld	hl, ___end_of_line_str
	call	puts_loop
	ret

puts_loop:
	ld	a, (hl)
	or	a, a
	ret	z
	ld	e, a
	push	hl
	push	de
	call	_putchar
	pop	de
	pop	hl
	inc	hl
	jr	puts_loop

	section .rodata
	.global 	___null_literal_str
___null_literal_str:
	db	"(NULL)", 0

	.global	___end_of_line_str
___end_of_line_str:
	db	10, 0

	extern	_putchar

