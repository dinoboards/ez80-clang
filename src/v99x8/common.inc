
; V9958 REGISTERS
VDP_DATA:	equ	$FF98		; VDP data port (VRAM read/write)
VDP_ADDR:	equ	$FF99		; VDP address (write only)
VDP_STAT:	equ	$FF99		; VDP status (read only)
VDP_PALT:	equ	$FF9A		; VDP palette latch (write only)
VDP_REGS:	equ	$FF9B		; VDP register access (write only)

.if ENABLE_DELAY=1
.macro	DELAY_1_7US  ; approx 1.7 us @25Mhz CPU
	PUSH	AF
	POP	AF
	PUSH	AF
	POP	AF
	NOP
	NOP
.endm
.else
.macro	DELAY_1_7US
.endm
.endif
