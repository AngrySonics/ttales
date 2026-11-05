*
* Modulator Offset Table
*

	dc.b	$14,$00		; Offset to modulator #0: 20
	dc.b	$1D,$00		; Offset to modulator #1: 29
	dc.b	$2C,$00		; Offset to modulator #2: 44
	dc.b	$35,$00		; Offset to modulator #3: 53
	dc.b	$4A,$00		; Offset to modulator #4: 74
	dc.b	$5F,$00		; Offset to modulator #5: 95
	dc.b	$65,$00		; Offset to modulator #6: 101
	dc.b	$6B,$00		; Offset to modulator #7: 107
	dc.b	$86,$00		; Offset to modulator #8: 134
	dc.b	$8F,$00		; Offset to modulator #9: 143
*
* Modulator Data
*

* Modulator 0 "SusDn Pitch 1.step": Pitch
	dc.b	$00,$00			; initial value = 0
	dc.b	$06,$00,$00		; len = 6, slope = 0
	dc.b	$17,$C7,$FF		; len = 23, slope = -57
	dc.b	0
* Modulator 1 "Up Pitch 1.step": Pitch
	dc.b	$00,$00			; initial value = 0
	dc.b	$06,$00,$00		; len = 6, slope = 0
	dc.b	$15,$08,$00		; len = 21, slope = 8
	dc.b	$01,$00,$00		; len = 1, slope = 0
	dc.b	$03,$C9,$FF		; len = 3, slope = -55
	dc.b	0
* Modulator 2 "Fast up": Pitch
	dc.b	$00,$00			; initial value = 0
	dc.b	$04,$00,$02		; len = 4, slope = 512
	dc.b	$04,$00,$FE		; len = 4, slope = -512
	dc.b	0
* Modulator 3 "Fast WoW": Pitch
	dc.b	$00,$00			; initial value = 0
	dc.b	$02,$40,$00		; len = 2, slope = 64
	dc.b	$03,$C0,$FF		; len = 3, slope = -64
	dc.b	$03,$40,$00		; len = 3, slope = 64
	dc.b	$03,$C0,$FF		; len = 3, slope = -64
	dc.b	$03,$40,$00		; len = 3, slope = 64
	dc.b	$02,$C0,$FF		; len = 2, slope = -64
	dc.b	0
* Modulator 4 "Big WoW": Pitch
	dc.b	$00,$00			; initial value = 0
	dc.b	$03,$00,$01		; len = 3, slope = 256
	dc.b	$06,$00,$FF		; len = 6, slope = -256
	dc.b	$06,$00,$01		; len = 6, slope = 256
	dc.b	$06,$00,$FF		; len = 6, slope = -256
	dc.b	$06,$00,$01		; len = 6, slope = 256
	dc.b	$03,$00,$FF		; len = 3, slope = -256
	dc.b	0
* Modulator 5 "Down Slide": Pitch
	dc.b	$00,$07			; initial value = 1792
	dc.b	$70,$F0,$FF		; len = 112, slope = -16
	dc.b	0
* Modulator 6 "Dn Pitch 1.step": Pitch
	dc.b	$00,$00			; initial value = 0
	dc.b	$0E,$A2,$FF		; len = 14, slope = -94
	dc.b	0
* Modulator 7 "Fast Mod": Pitch
	dc.b	$00,$00			; initial value = 0
	dc.b	$02,$20,$00		; len = 2, slope = 32
	dc.b	$04,$E0,$FF		; len = 4, slope = -32
	dc.b	$04,$20,$00		; len = 4, slope = 32
	dc.b	$04,$E0,$FF		; len = 4, slope = -32
	dc.b	$04,$20,$00		; len = 4, slope = 32
	dc.b	$04,$E0,$FF		; len = 4, slope = -32
	dc.b	$04,$20,$00		; len = 4, slope = 32
	dc.b	$02,$E0,$FF		; len = 2, slope = -32
	dc.b	0
* Modulator 8 "Buoing": Pitch
	dc.b	$00,$00			; initial value = 0
	dc.b	$19,$2C,$01		; len = 25, slope = 300
	dc.b	$43,$50,$FB		; len = 67, slope = -1200
	dc.b	0
* Modulator 9 " Up Pitch 8ct": Pitch
	dc.b	$00,$00			; initial value = 0
	dc.b	$77,$18,$00		; len = 119, slope = 24
	dc.b	$03,$68,$FC		; len = 3, slope = -920
	dc.b	0
