
.macro	EZ80_FN
	RST.L	$10
.endm

.macro	EZ80_DELAY
	RST.L	$18
.endm

.macro	EZ80_UTIL_GET_CPU_FQ
	xor	a
	ld	b, 5
	EZ80_FN
.endm

.macro	EZ80_UTIL_MEMTM_GET
	xor	a
	ld	b, 10
	EZ80_FN
.endm

.macro	EZ80_UTIL_IOTM_GET
	xor	a
	ld	b, 11
	EZ80_FN
.endm


.macro	EZ80_UTIL_MEMTM_SET
	xor	a
	ld	b, 8
	EZ80_FN
.endm

.macro	EZ80_UTIL_IOTM_SET
	xor	a
	ld	b, 9
	EZ80_FN
.endm

.macro	EZ80_UTIL_MEM0TM_SET
	xor	a
	ld	b, 1
	EZ80_FN
.endm

.macro	EZ80_UTIL_MEM1TM_SET
	xor	a
	ld	b, 2
	EZ80_FN
.endm

.macro	EZ80_UTIL_DEBUG
	xor	a
	ld	b, 7
	EZ80_FN
.endm

.macro	EZ80_UTIL_FLSHWS_SET
	xor	a
	ld	b, 14
	EZ80_FN
.endm

.macro	EZ80_UTIL_FLSHWS_GET
	xor	a
	ld	b, 15
	EZ80_FN
.endm

.macro SYSUTL_EMULSTAT_GET
	xor	a
	ld	b, 19
	EZ80_FN
.endm

.macro	EZ80_UTIL_TMR_FREQTICK_GET
	ld	a, 2
	ld	b, 4
	EZ80_FN
.endm

.macro	EZ80_UTIL_TMR_FREQTICK_SET
	ld	a, 2
	ld	b, 5
	EZ80_FN
.endm

.macro	EZ80_UTIL_TMR_TICK_GET
	ld	a, 2
	ld	b, 0
	EZ80_FN
.endm

.macro	EZ80_UTIL_TMR_TICK_SET
	ld	a, 2
	ld	b, 2
	EZ80_FN
.endm

.macro	EZ80_UART_OUT
	ld	a, 3
	ld	b, 1
	EZ80_FN
.endm

.macro	EZ80_UART_IN
	ld	a, 3
	ld	b, 0
	EZ80_FN
.endm

.macro	EZ80_USB_KYB_FLUSH
	ld	a, 6
	ld	b, 34
	EZ80_FN
.endm

.macro	EZ80_USB_KYB_RPT
	ld	a, 6
	ld	b, 35
	EZ80_FN
.endm

.macro	EZ80_USB_KYB_EVNT
	ld	a, 6
	ld	b, 36
	EZ80_FN
.endm

.macro	EZ80_USBT_GET_DESC2
	ld	a, 6
	ld	b, 133
	EZ80_FN
.endm

.macro	EZ80_USBT_GET_FULL_DESC
	ld	a, 6
	ld	b, 135
	EZ80_FN
.endm

.macro	EZ80_USB_CONTROL_TRANSFER
	ld	a, 6
	ld	b, 128
	EZ80_FN
.endm

.macro	EZ80_USB_DATA_IN_TRANSFER
	ld	a, 6
	ld	b, 129
	EZ80_FN
.endm

.macro	EZ80_USB_GET_DEV_TYP
	ld	a, 6
	ld	b, 253
	EZ80_FN
.endm

.macro	EZ80_USB_MSE_INIT
	ld	a, 6
	ld	b, 48
	EZ80_FN
.endm

.macro	EZ80_USB_MSE_READ
	ld	a, 6
	ld	b, 49
	EZ80_FN
.endm

.macro	EZ80_EMULATOR_INVOKE addr
	ld	a, 7
	ld	iy, \addr
	EZ80_FN
.endm

;A=2, B=0 SYSTMR_TICKS_GET
;   #DEFINE EZ80_UTIL_VER_EXCH		XOR A \ LD B, 0 \ EZ80_FN
;   #DEFINE EZ80_UTIL_DELAY 		XOR A \ LD B, 1 \ EZ80_FN
;   #DEFINE EZ80_UTIL_SET_BUSTM 		XOR A \ LD B, 3 \ EZ80_FN
;   #DEFINE EZ80_UTIL_SET_BUSFQ 		XOR A \ LD B, 4 \ EZ80_FN
;   #DEFINE EZ80_UTIL_GET_CPU_FQ 		XOR A \ LD B, 5 \ EZ80_FN
;   #DEFINE EZ80_UTIL_DEBUG 		XOR A \ LD B, 7 \ EZ80_FN
;   #DEFINE EZ80_UTIL_MEMTM_SET 		XOR A \ LD B, 8 \ EZ80_FN
;   #DEFINE EZ80_UTIL_IOTM_SET 		XOR A \ LD B, 9 \ EZ80_FN
;   #DEFINE EZ80_UTIL_MEMTM_GET 		XOR A \ LD B, 10 \ EZ80_FN
;   #DEFINE EZ80_UTIL_IOTM_GET 		XOR A \ LD B, 11 \ EZ80_FN
;   #DEFINE EZ80_UTIL_MEMTMFQ_SET		XOR A \ LD B, 12 \ EZ80_FN
;   #DEFINE EZ80_UTIL_IOTMFQ_SET		XOR A \ LD B, 13 \ EZ80_FN
;   #DEFINE EZ80_UTIL_FLSHWS_SET		XOR A \ LD B, 14 \ EZ80_FN
;   #DEFINE EZ80_UTIL_FLSHWS_GET		XOR A \ LD B, 15 \ EZ80_FN
;   #DEFINE EZ80_UTIL_FLSHFQ_SET		XOR A \ LD B, 16 \ EZ80_FN
