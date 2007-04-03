.segment "HEADER"
	.byte "NES"
	
.segment "VECTORS"
		
	.word $8000
	.word $8000
	.word $8000
	.word $8000
	.word $8000
	.word $8000	

.segment "CODE"

	;; clear out 256 bytes of memory starting at $200
	lda	#00
	sta	$00
	lda	#03
	sta	$01
	
	ldx	#5

	jsr	fill

	brk

.proc fill
	;; fills memory with decreasing integers starting
	;; at one, and going through a certain length
	;; 0x00, 0x01 - 16-bit begin address of array
	;; X - length
	
	ldy	#0

beginloop:
	
	txa
	beq	endproc

	;; move x to a
	txa
	sta	($00), Y

	iny
	dex

	jmp	beginloop
	
	
endproc:
	
	rts
	
.endproc

.proc sort
	;; sort expects the 16-bit begin address of the array
	;; to sort to be at 0x00 and 0x01. The length of the array
	;; should be in X
	
	;; for (i = 0; i < length; i++) - i gets $200, length gets $202
	lda	#00
	sta	$200
	stx	$202

outerloop:
	lda	$200
	sec
	sbc	$202
	bmi	innerloop
	jmp	endproc
	
	;; for (j = 0; j < i - 1; j++) - j gets $201
	lda	#0
	sta	$201
	;; temp at $204 stores curMin
	lda	#255
	sta	$204

innerloop:	

	;; temp at $203, store i - 1
	ldx	$200
	dex
	txa
	sec
	sbc	$201
	bpi	withininnerloop
	jmp	outerloop

withininnerloop:

	;; if (array[
	
	
		
	;; add 1 to j
	inc	$201
	jmp	innerloop

	;; add 1 to i
	inc	$200
	jmp	outerloop
	
	
endproc:
	rts
	
.endproc