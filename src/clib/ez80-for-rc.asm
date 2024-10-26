	.assume	adl = 1

	section	.text,"ax",@progbits
	.global	_putchar


__bdos	= 0x5;

; int putchar(int character) {
_putchar:
	push	ix
	ld	ix, 0
	add	ix, sp
	ld	de, (ix + 6)

	XOR	A
	LD	B,7
	RST.L	$10

	CALL.SIS	_putchar_z80 & 0xFFFF

	pop	ix
	RET

	.assume	adl = 0
_putchar_z80:

	ld      c,2
	CALL	__bdos
	RET.L

	.assume	adl = 1

	.global	_fputc
; int fputc(int c, FILE *stream)
_fputc:
	RET
