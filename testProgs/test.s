;
; File generated by cc65 v 2.11.0
;
	.fopt		compiler,"cc65 v 2.11.0"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	off
	.importzp	sp, sreg, regsave, regbank, tmp1, ptr1, ptr2
	.macpack	longbranch
	.export		_main

; ---------------------------------------------------------------
; int __near__ main ()
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_main: near

	.forceimport	initmainargs

.segment	"CODE"

	jsr     enter
	lda     #$42
	jsr     pusha
	jsr     decsp2
	ldx     #$00
	lda     #$79
	ldy     #$00
	jsr     staxysp
	ldy     #$01
	jsr     ldaxysp
	jsr     pushax
	ldy     #$04
	ldx     #$00
	lda     (sp),y
	ldy     #$00
	jsr     staspidx
	ldy     #$01
	jsr     ldaxysp
	ldy     #$00
	jsr     ldauidx
	jmp     L0002
L0002:	ldy     #$03
	jsr     leavey
	rts

.endproc

