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

	ld      c,2
	CALL	cpm_bdos

	pop	ix
	RET

	extern	cpm_bdos
