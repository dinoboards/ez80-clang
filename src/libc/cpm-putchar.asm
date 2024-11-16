	.assume	adl=1

	section	.text, "ax", @progbits
	.global	_putchar


__bdos	=	$5;

; int putchar(int character) {
_putchar:
	call	__frameset0
	ld	de, (ix+6)

	ld	c, 2
	call.sis cpm_bdos_z80 & $FFFF

	pop	ix
	ret

	extern	cpm_bdos_z80
