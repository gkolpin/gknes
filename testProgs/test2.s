.segment "HEADER"

	.byte "NES"

.segment "CODE"

	lda	#$5
	pha	
	jsr	fact
	brk

.proc	add

	;; Add expects that the two arguments are at addresses
	;; $00 and $01. The result goes into $00
	
	lda	$00
	adc	$01
	sta	$00
	rts

.endproc

	
.proc fact
	;; This is a recursive procedure.
	;; The argument is placed on the stack

	;; if arg == 0, return 1

	tsx
	lda	$0102, X
	beq	return_one

	;; otherwise subtract one from the argument,
	;; push it on the stack, call fact again, and
	;; multiply the return with the argument
	
	sec
	sbc	#$1
	pha
	jsr	fact

	;; now multiply it by $02
	pla
	tsx
	lda	$102, X
	sta	$01
	jsr	mult
	rts

return_one:
	lda	#$1
	sta	$00
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
	


.segment "VECTORS"
	
	.word $8000
	.word $8000
	.word $8000
	.word $8000
	.word $8000
	.word $8000	