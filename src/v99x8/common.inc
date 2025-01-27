

CMD_PSET	equ	$50
CMD_LINE	equ	$70
CMD_LMMV	equ	$80
CMD_LMMM	equ	$90
CMD_HMMV	equ	$C0
CMD_HMMM	equ	$D0
CMD_HMMC	equ	$F0

.macro	EZ80_DELAY
	rst.l	$18
.endm

.if ENABLE_DELAY=1
.macro	DELAY_1_7US  ; approx 1.7 us @25Mhz CPU
	push	af
	pop	af
	push	af
	pop	af
	push	af
	pop	af
	push	af
	pop	af
	nop
	nop
.endm

.macro	DELAY_VDP
	EZ80_DELAY ; 5-6us seconds
.endm

.else
.macro	DELAY_1_7US
.endm
.macro	DELAY_VDP
.endm
.endif
