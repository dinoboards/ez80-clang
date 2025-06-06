
CMD_PSET	equ	$50
CMD_LINE	equ	$70
CMD_LMMV	equ	$80
CMD_LMMM	equ	$90
CMD_LMMC	equ	$B0
CMD_HMMV	equ	$C0
CMD_HMMM	equ	$D0
CMD_HMMC	equ	$F0

CSX_WAIT_7	equ	(7 << 5)
CSX_WAIT_6	equ	(6 << 5)
CSX_WAIT_5	equ	(5 << 5)
CSX_WAIT_4	equ	(4 << 5)
CSX_WAIT_3	equ	(3 << 5)
CSX_WAIT_2	equ	(2 << 5)
CSX_WAIT_1	equ	(1 << 5)
CSX_WAIT_0	equ	(0 << 5)
CSX_TYPE_IO	equ	$10
CSX_TYPE_MEM	equ	0
CSX_ENABLED	equ	$08
CSX_DISABLED	equ	0

;* Chip Select
CS0_LBR:	equ	$A8
CS0_UBR:	equ	$A9
CS0_CTL:	equ	$AA
CS1_LBR:	equ	$AB
CS1_UBR:	equ	$AC
CS1_CTL:	equ	$AD
CS2_LBR:	equ	$AE
CS2_UBR:	equ	$AF
CS2_CTL:	equ	$B0
CS3_LBR:	equ	$B1
CS3_UBR:	equ	$B2
CS3_CTL:	equ	$B3

;* CSBMC Registers
CS0_BMC:	equ	$F0
CS1_BMC:	equ	$F1
CS2_BMC:	equ	$F2
CS3_BMC:	equ	$F3

BMX_BM_EZ80		equ	($00 << 6)
BMX_BM_Z80		equ	($01 << 6)
BMX_BM_INTEL		equ	($02 << 6)
BMX_BM_MOTOROLA		equ	($03 << 6)
BMX_AD_SEPARATE		equ	($0 << 5)
BMX_AD_MULTIPLEX	equ	($1 << 5)
BMX_BC_0		equ	$00
BMX_BC_1		equ	$01
BMX_BC_2		equ	$02
BMX_BC_3		equ	$03
BMX_BC_4		equ	$04
BMX_BC_5		equ	$05
BMX_BC_6		equ	$06
BMX_BC_7		equ	$07
BMX_BC_8		equ	$08
BMX_BC_9		equ	$09
BMX_BC_10		equ	$0A
BMX_BC_11		equ	$0B
BMX_BC_12		equ	$0C
BMX_BC_13		equ	$0D
BMX_BC_14		equ	$0E
BMX_BC_15		equ	$0F

.if VDP_V9958=1
.macro	SET_SLOW_IO_SPEED
	IN0	A, (CS2_BMC)					; SAVE CURRENT CS2 (EXT IO) TIMING
	PUSH	AF

	LD	A, BMX_BM_Z80 | BMX_AD_SEPARATE | BMX_BC_15	; SET I/O TIMING TO 15BC
	OUT0	(CS2_BMC), A
.endm

.macro	RESTORE_IO_SPEED
	POP	AF
	OUT0	(CS2_BMC), A
.endm

.else
.macro	SET_SLOW_IO_SPEED
.endm
.macro	RESTORE_IO_SPEED
.endm
.endif

.macro	DI_AND_SAVE
	ld	a, i ; P = IEF2
	di
	push	af
.endm

.macro	RESTORE_EI
	pop	af
	jp	po, .skipEI
	ei
.skipEI:
.endm
