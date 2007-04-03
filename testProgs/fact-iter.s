.segment "HEADER"
	.byte "nes"

.segment "VECTORS"

	.word $8000
	.word $8000
	.word $8000
	.word $8000
	.word $8000
	.word $8000

.segment "CODE"

	lda	#4
	jsr	factiter
	brk

.proc factiter
	
	;; argument comes in on A
	;; result goes out on A
	tax
	cmp	#0
	clc
	beq	return_one
	
	;; result = 1
	lda	#1
	sta	$03
	
loop:
	;; for (i = n; i > 1; i--){
	;;	n * result;
	;; }
	txa
	cmp	#1
	clc
	beq	done
	
	lda	$03

	sta	$00
	stx	$01

	stx	$04

	jsr	mult

	lda	$00
	sta	$03
	
	ldx	$04
	dex

	jmp	loop

return_one:
	lda	#1
	rts
	
done:

	lda	$03
	rts

.endproc

.proc	mult

	;; multiply expects that the two arguments are at addresses
	;; $00 and $01. The result goes into $00

	;; first move $00 to $02

	lda	$00
	sta	$02

	;; now make $00 = #$0 
	
	lda	#$0
	sta	$00

	;; now make X = $01, and if it equals zero, jump
	;; to end

	lda	$01
	beq	end
	tax
	lda	#$0

iter:

	adc	$02
	dex
	beq	end
	jmp	iter

end:
	sta	$00
	rts
	
.endproc	