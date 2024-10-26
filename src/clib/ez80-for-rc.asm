	.assume	adl = 1

	section	.text,"ax",@progbits
	.global	_putchar

; int putchar(int character) {

_putchar:
	RET

	.global	_fputc

; int fputc(int c, FILE *stream)
_fputc:
	RET
