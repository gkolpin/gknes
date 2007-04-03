#ifndef OPCODE_MAP_H
#define OPCODE_MAP_H

#include "opcodes.h"

/*
 * IM - implied
 * I - immediate
 * Z - zero page
 * A - absolute
 * AC - accumulator
 * IN - indirect (JMP)
 */

#define IM 0
#define I 1
#define Z 2
#define ZX 3
#define ZY a
#define A 4
#define AX 5
#define AY 6
#define IX 7
#define IY 8
#define IN 9
#define AC b

#define ADC 01
#define AND 02
#define ASL 03
#define BCC 04
#define BCS 05
#define BEQ 06
#define BIT 07
#define BMI 08
#define BNE 09
#define BPL 0A
#define BRK 0B
#define BVC 0C
#define BVS 0D
#define CLC 0E
#define CLD 0F
#define CLI 10
#define CLV 11
#define CMP 12
#define CPX 13
#define CPY 14
#define DEC 15
#define DEX 16
#define DEY 17
#define EOR 18
#define INC 19
#define INX 1A
#define INY 1B
#define JMP 1C
#define JSR 1D
#define LDA 1E
#define LDX 1F
#define LDY 20
#define LSR 21
#define NOP 22
#define ORA 23
#define PHA 24
#define PHP 25
#define PLA 26
#define PLP 27
#define ROL 28
#define ROR 29
#define RTI 2A
#define RTS 2B
#define SBC 2C
#define SEC 2D
#define SED 2E
#define SEI 2F
#define STA 30
#define STX 31
#define STY 32
#define TAX 33
#define TAY 34
#define TSX 35
#define TXA 36
#define TXS 37
#define TYA 38

#define HEXIFY(N) 0x ## N
#define HEXIFY_N(N) HEXIFY(N)
#define GLUE_CODES(CODE1, CODE2) HEXIFY(CODE1) * 256 + HEXIFY(CODE2)

typedef unsigned short opcode_16;
#define GET_OP16(opcode) opcode_map[opcode]
#define GET_OP16_CLASS(opcode16) opcode16 >> 8
#define GET_OP16_TYPE(opcode16) opcode16 & 0xFF

int opcode_map[256];
int cycle_map[256];
int page_penalties[256];

void initOpcodeMap(){
  //first init opcode_map
  opcode_map[ADC_I] = GLUE_CODES(ADC, I);
  opcode_map[ADC_Z] = GLUE_CODES(ADC, Z);
  opcode_map[ADC_ZX] = GLUE_CODES(ADC, ZX);
  opcode_map[ADC_A] = GLUE_CODES(ADC, A);
  opcode_map[ADC_AX] = GLUE_CODES(ADC, AX);
  opcode_map[ADC_AY] = GLUE_CODES(ADC, AY);
  opcode_map[ADC_IX] = GLUE_CODES(ADC, IX);
  opcode_map[ADC_IY] = GLUE_CODES(ADC, IY);
  opcode_map[AND_I] = GLUE_CODES(AND, I);
  opcode_map[AND_Z] = GLUE_CODES(AND, Z);
  opcode_map[AND_ZX] = GLUE_CODES(AND, ZX);
  opcode_map[AND_A] = GLUE_CODES(AND, A);
  opcode_map[AND_AX] = GLUE_CODES(AND, AX);
  opcode_map[AND_AY] = GLUE_CODES(AND, AY);
  opcode_map[AND_IX] = GLUE_CODES(AND, IX);
  opcode_map[AND_IY] = GLUE_CODES(AND, IY);
  opcode_map[ASL_IM] = GLUE_CODES(ASL, IM);
  opcode_map[ASL_Z] = GLUE_CODES(ASL, Z);
  opcode_map[ASL_ZX] = GLUE_CODES(ASL, ZX);
  opcode_map[ASL_A] = GLUE_CODES(ASL, A);
  opcode_map[ASL_AX] = GLUE_CODES(ASL, AX);
  opcode_map[BCC_I] = GLUE_CODES(BCC, I);
  opcode_map[BCS_I] = GLUE_CODES(BCS, I);
  opcode_map[BEQ_I] = GLUE_CODES(BEQ, I);
  opcode_map[BIT_Z] = GLUE_CODES(BIT, Z);
  opcode_map[BIT_A] = GLUE_CODES(BIT, A);
  opcode_map[BMI_I] = GLUE_CODES(BMI, I);
  opcode_map[BNE_I] = GLUE_CODES(BNE, I);
  opcode_map[BPL_I] = GLUE_CODES(BPL, I);
  opcode_map[BRK_IM] = GLUE_CODES(BRK, IM);
  opcode_map[BVC_I] = GLUE_CODES(BVC, I);
  opcode_map[BVS_I] = GLUE_CODES(BVS, I);
  opcode_map[CLC_IM] = GLUE_CODES(CLC, IM);
  opcode_map[CLD_IM] = GLUE_CODES(CLD, IM);
  opcode_map[CLI_IM] = GLUE_CODES(CLI, IM);
  opcode_map[CLV_IM] = GLUE_CODES(CLV, IM);
  opcode_map[CMP_I] = GLUE_CODES(CMP, I);
  opcode_map[CMP_Z] = GLUE_CODES(CMP, Z);
  opcode_map[CMP_ZX] = GLUE_CODES(CMP, ZX);
  opcode_map[CMP_A] = GLUE_CODES(CMP, A);
  opcode_map[CMP_AX] = GLUE_CODES(CMP, AX);
  opcode_map[CMP_AY] = GLUE_CODES(CMP, AY);
  opcode_map[CMP_IX] = GLUE_CODES(CMP, IX);
  opcode_map[CMP_IY] = GLUE_CODES(CMP, IY);
  opcode_map[CPX_I] = GLUE_CODES(CPX, I);
  opcode_map[CPX_Z] = GLUE_CODES(CPX, Z);
  opcode_map[CPX_A] = GLUE_CODES(CPX, A);
  opcode_map[CPY_I] = GLUE_CODES(CPY, I);
  opcode_map[CPY_Z] = GLUE_CODES(CPY, Z);
  opcode_map[CPY_A] = GLUE_CODES(CPY, A);
  opcode_map[DEC_Z] = GLUE_CODES(DEC, Z);
  opcode_map[DEC_ZX] = GLUE_CODES(DEC, ZX);
  opcode_map[DEC_A] = GLUE_CODES(DEC, A);
  opcode_map[DEC_AX] = GLUE_CODES(DEC, AX);
  opcode_map[DEX_IM] = GLUE_CODES(DEX, IM);
  opcode_map[DEY_IM] = GLUE_CODES(DEY, IM);
  opcode_map[EOR_I] = GLUE_CODES(EOR, I);
  opcode_map[EOR_Z] = GLUE_CODES(EOR, Z);
  opcode_map[EOR_ZX] = GLUE_CODES(EOR, ZX);
  opcode_map[EOR_A] = GLUE_CODES(EOR, A);
  opcode_map[EOR_AX] = GLUE_CODES(EOR, AX);
  opcode_map[EOR_AY] = GLUE_CODES(EOR, AY);
  opcode_map[EOR_IX] = GLUE_CODES(EOR, IX);
  opcode_map[EOR_IY] = GLUE_CODES(EOR, IY);
  opcode_map[INC_Z] = GLUE_CODES(INC, Z);
  opcode_map[INC_ZX] = GLUE_CODES(INC, ZX);
  opcode_map[INC_A] = GLUE_CODES(INC, A);
  opcode_map[INC_AX] = GLUE_CODES(INC, AX);
  opcode_map[INX_IM] = GLUE_CODES(INX, IM);
  opcode_map[INY_IM] = GLUE_CODES(INY, IM);
  opcode_map[JMP_A] = GLUE_CODES(JMP, A);
  opcode_map[JMP_IN] = GLUE_CODES(JMP, IN);
  opcode_map[JSR_A] = GLUE_CODES(JSR, A);
  opcode_map[LDA_I] = GLUE_CODES(LDA, I);
  opcode_map[LDA_Z] = GLUE_CODES(LDA, Z);
  opcode_map[LDA_ZX] = GLUE_CODES(LDA, ZX);
  opcode_map[LDA_A] = GLUE_CODES(LDA, A);
  opcode_map[LDA_AX] = GLUE_CODES(LDA, AX);
  opcode_map[LDA_AY] = GLUE_CODES(LDA, AY);
  opcode_map[LDA_IX] = GLUE_CODES(LDA, IX);
  opcode_map[LDA_IY] = GLUE_CODES(LDA, IY);
  opcode_map[LDX_I] = GLUE_CODES(LDX, I);
  opcode_map[LDX_Z] = GLUE_CODES(LDX, Z);
  opcode_map[LDX_ZY] = GLUE_CODES(LDX, ZY);
  opcode_map[LDX_A] = GLUE_CODES(LDX, A);
  opcode_map[LDX_AY] = GLUE_CODES(LDX, AY);
  opcode_map[LDY_I] = GLUE_CODES(LDY, I);
  opcode_map[LDY_Z] = GLUE_CODES(LDY, Z);
  opcode_map[LDY_ZX] = GLUE_CODES(LDY, ZX);
  opcode_map[LDY_A] = GLUE_CODES(LDY, A);
  opcode_map[LDY_AX] = GLUE_CODES(LDY, AX);
  opcode_map[LSR_AC] = GLUE_CODES(LSR, A);
  opcode_map[LSR_Z] = GLUE_CODES(LSR, Z);
  opcode_map[LSR_ZX] = GLUE_CODES(LSR, ZX);
  opcode_map[LSR_A] = GLUE_CODES(LSR, AC);
  opcode_map[LSR_AX] = GLUE_CODES(LSR, AX);
  opcode_map[NOP_IM] = GLUE_CODES(NOP, IM);
  opcode_map[ORA_I] = GLUE_CODES(ORA, I);
  opcode_map[ORA_Z] = GLUE_CODES(ORA, Z);
  opcode_map[ORA_ZX] = GLUE_CODES(ORA, ZX);
  opcode_map[ORA_A] = GLUE_CODES(ORA, A);
  opcode_map[ORA_AX] = GLUE_CODES(ORA, AX);
  opcode_map[ORA_AY] = GLUE_CODES(ORA, AY);
  opcode_map[ORA_IX] = GLUE_CODES(ORA, IX);
  opcode_map[ORA_IY] = GLUE_CODES(ORA, IY);
  opcode_map[PHA_IM] = GLUE_CODES(PHA, IM);
  opcode_map[PHP_IM] = GLUE_CODES(PHP, IM);
  opcode_map[PLA_IM] = GLUE_CODES(PLA, IM);
  opcode_map[PLP_IM] = GLUE_CODES(PLP, IM);
  opcode_map[ROL_AC] = GLUE_CODES(ROL, AC);
  opcode_map[ROL_Z] = GLUE_CODES(ROL, Z);
  opcode_map[ROL_ZX] = GLUE_CODES(ROL, ZX);
  opcode_map[ROL_A] = GLUE_CODES(ROL, A);
  opcode_map[ROL_AX] = GLUE_CODES(ROL, AX);
  opcode_map[ROR_AC] = GLUE_CODES(ROR, AC);
  opcode_map[ROR_Z] = GLUE_CODES(ROR, Z);
  opcode_map[ROR_ZX] = GLUE_CODES(ROR, ZX);
  opcode_map[ROR_A] = GLUE_CODES(ROR, A);
  opcode_map[ROR_AX] = GLUE_CODES(ROR, AX);
  opcode_map[RTI_IM] = GLUE_CODES(RTI, IM);
  opcode_map[RTS_IM] = GLUE_CODES(RTS, IM);
  opcode_map[SBC_I] = GLUE_CODES(SBC, I);
  opcode_map[SBC_Z] = GLUE_CODES(SBC, Z);
  opcode_map[SBC_ZX] = GLUE_CODES(SBC, ZX);
  opcode_map[SBC_A] = GLUE_CODES(SBC, A);
  opcode_map[SBC_AX] = GLUE_CODES(SBC, AX);
  opcode_map[SBC_AY] = GLUE_CODES(SBC, AY);
  opcode_map[SBC_IX] = GLUE_CODES(SBC, IX);
  opcode_map[SBC_IY] = GLUE_CODES(SBC, IY);
  opcode_map[SEC_IM] = GLUE_CODES(SEC, IM);
  opcode_map[SED_IM] = GLUE_CODES(SED, IM);
  opcode_map[SEI_IM] = GLUE_CODES(SEI, IM);
  opcode_map[STA_Z] = GLUE_CODES(STA, Z);
  opcode_map[STA_ZX] = GLUE_CODES(STA, ZX);
  opcode_map[STA_A] = GLUE_CODES(STA, A);
  opcode_map[STA_AX] = GLUE_CODES(STA, AX);
  opcode_map[STA_AY] = GLUE_CODES(STA, AY);
  opcode_map[STA_IX] = GLUE_CODES(STA, IX);
  opcode_map[STA_IY] = GLUE_CODES(STA, IY);
  opcode_map[STX_Z] = GLUE_CODES(STX, Z);
  opcode_map[STX_ZY] = GLUE_CODES(STX, ZY);
  opcode_map[STX_A] = GLUE_CODES(STX, A);
  opcode_map[STY_Z] = GLUE_CODES(STY, Z);
  opcode_map[STY_ZY] = GLUE_CODES(STY, ZY);
  opcode_map[STY_A] = GLUE_CODES(STY, A);
  opcode_map[TAX_IM] = GLUE_CODES(TAX, IM);
  opcode_map[TAY_IM] = GLUE_CODES(TAY, IM);
  opcode_map[TSX_IM] = GLUE_CODES(TSX, IM);
  opcode_map[TXA_IM] = GLUE_CODES(TXA, IM);
  opcode_map[TXS_IM] = GLUE_CODES(TXS, IM);
  opcode_map[TYA_IM] = GLUE_CODES(TYA, IM);

  //now itit cycle_map
  cycle_map[ADC_I] = 2;
  cycle_map[ADC_Z] = 3;
  cycle_map[ADC_ZX] = 4;
  cycle_map[ADC_A] = 4;
  cycle_map[ADC_AX] = 4;
  cycle_map[ADC_AY] = 4;
  cycle_map[ADC_IX] = 6;
  cycle_map[ADC_IY] = 5;
  cycle_map[AND_I] = 2;
  cycle_map[AND_Z] = 3;
  cycle_map[AND_ZX] = 4;
  cycle_map[AND_A] = 4;
  cycle_map[AND_AX] = 4;
  cycle_map[AND_AY] = 4;
  cycle_map[AND_IX] = 6;
  cycle_map[AND_IY] = 5;
  cycle_map[ASL_IM] = 2;
  cycle_map[ASL_Z] = 5;
  cycle_map[ASL_ZX] = 6;
  cycle_map[ASL_A] = 6;
  cycle_map[ASL_AX] = 7;
  cycle_map[BCC_I] = 2;
  cycle_map[BCS_I] = 2;
  cycle_map[BEQ_I] = 2;
  cycle_map[BIT_Z] = 3;
  cycle_map[BIT_A] = 4;
  cycle_map[BMI_I] = 2;
  cycle_map[BNE_I] = 2;
  cycle_map[BPL_I] = 2;
  cycle_map[BRK_IM] = 7;
  cycle_map[BVC_I] = 2;
  cycle_map[BVS_I] = 2;
  cycle_map[CLC_IM] = 2;
  cycle_map[CLD_IM] = 2;
  cycle_map[CLI_IM] = 2;
  cycle_map[CLV_IM] = 2;
  cycle_map[CMP_I] = 2;
  cycle_map[CMP_Z] = 3;
  cycle_map[CMP_ZX] = 4;
  cycle_map[CMP_A] = 4;
  cycle_map[CMP_AX] = 4;
  cycle_map[CMP_AY] = 4;
  cycle_map[CMP_IX] = 6;
  cycle_map[CMP_IY] = 5;
  cycle_map[CPX_I] = 2;
  cycle_map[CPX_Z] = 3;
  cycle_map[CPX_A] = 4;
  cycle_map[CPY_I] = 2;
  cycle_map[CPY_Z] = 3;
  cycle_map[CPY_A] = 4;
  cycle_map[DEC_Z] = 5;
  cycle_map[DEC_ZX] = 6;
  cycle_map[DEC_A] = 6;
  cycle_map[DEC_AX] = 7;
  cycle_map[DEX_IM] = 2;
  cycle_map[DEY_IM] = 2;
  cycle_map[EOR_I] = 2;
  cycle_map[EOR_Z] = 3;
  cycle_map[EOR_ZX] = 4;
  cycle_map[EOR_A] = 4;
  cycle_map[EOR_AX] = 4;
  cycle_map[EOR_AY] = 4;
  cycle_map[EOR_IX] = 6;
  cycle_map[EOR_IY] = 5;
  cycle_map[INC_Z] = 5;
  cycle_map[INC_ZX] = 6;
  cycle_map[INC_A] = 6;
  cycle_map[INC_AX] = 7;
  cycle_map[INX_IM] = 2;
  cycle_map[INY_IM] = 2;
  cycle_map[JMP_A] = 3;
  cycle_map[JMP_IN] = 5;
  cycle_map[JSR_A] = 6;
  cycle_map[LDA_I] = 2;
  cycle_map[LDA_Z] = 3;
  cycle_map[LDA_ZX] = 4;
  cycle_map[LDA_A] = 4;
  cycle_map[LDA_AX] = 4;
  cycle_map[LDA_AY] = 4;
  cycle_map[LDA_IX] = 6;
  cycle_map[LDA_IY] = 5;
  cycle_map[LDX_I] = 2;
  cycle_map[LDX_Z] = 3;
  cycle_map[LDX_ZY] = 4;
  cycle_map[LDX_A] = 4;
  cycle_map[LDX_AY] = 4;
  cycle_map[LDY_I] = 2;
  cycle_map[LDY_Z] = 3;
  cycle_map[LDY_ZX] = 4;
  cycle_map[LDY_A] = 4;
  cycle_map[LDY_AX] = 4;
  cycle_map[LSR_A] = 2;
  cycle_map[LSR_Z] = 5;
  cycle_map[LSR_ZX] = 6;
  cycle_map[LSR_A] = 6;
  cycle_map[LSR_AX] = 7;
  cycle_map[NOP_IM] = 2;
  cycle_map[ORA_I] = 2;
  cycle_map[ORA_Z] = 3;
  cycle_map[ORA_ZX] = 4;
  cycle_map[ORA_A] = 4;
  cycle_map[ORA_AX] = 4;
  cycle_map[ORA_AY] = 4;
  cycle_map[ORA_IX] = 6;
  cycle_map[ORA_IY] = 5;
  cycle_map[PHA_IM] = 3;
  cycle_map[PHP_IM] = 3;
  cycle_map[PLA_IM] = 4;
  cycle_map[PLP_IM] = 4;
  cycle_map[ROL_A] = 2;
  cycle_map[ROL_Z] = 5;
  cycle_map[ROL_ZX] = 6;
  cycle_map[ROL_A] = 6;
  cycle_map[ROL_AX] = 7;
  cycle_map[ROR_A] = 2;
  cycle_map[ROR_Z] = 5;
  cycle_map[ROR_ZX] = 6;
  cycle_map[ROR_A] = 6;
  cycle_map[ROR_AX] = 7;
  cycle_map[RTI_IM] = 6;
  cycle_map[RTS_IM] = 6;
  cycle_map[SBC_I] = 2;
  cycle_map[SBC_Z] = 3;
  cycle_map[SBC_ZX] = 4;
  cycle_map[SBC_A] = 4;
  cycle_map[SBC_AX] = 4;
  cycle_map[SBC_AY] = 4;
  cycle_map[SBC_IX] = 6;
  cycle_map[SBC_IY] = 5;
  cycle_map[SEC_IM] = 2;
  cycle_map[SED_IM] = 2;
  cycle_map[SEI_IM] = 2;
  cycle_map[STA_Z] = 3;
  cycle_map[STA_ZX] = 4;
  cycle_map[STA_A] = 4;
  cycle_map[STA_AX] = 5;
  cycle_map[STA_AY] = 5;
  cycle_map[STA_IX] = 6;
  cycle_map[STA_IY] = 6;
  cycle_map[STX_Z] = 3;
  cycle_map[STX_ZY] = 4;
  cycle_map[STX_A] = 4;
  cycle_map[STY_Z] = 3;
  cycle_map[STY_ZY] = 4;
  cycle_map[STY_A] = 4;
  cycle_map[TAX_IM] = 2;
  cycle_map[TAY_IM] = 2;
  cycle_map[TSX_IM] = 2;
  cycle_map[TXA_IM] = 2;
  cycle_map[TXS_IM] = 2;
  cycle_map[TYA_IM] = 2;

  //now init page_penalties
  int i;
  for (i = 0; i < 256; i++){
    page_penalties[i] = 0;
  }
   
  page_penalties[ADC_AX] = 1;
  page_penalties[ADC_AY] = 1;
  page_penalties[ADC_IY] = 1;

  page_penalties[AND_AX] = 1;
  page_penalties[AND_AY] = 1;
  page_penalties[AND_IY] = 1;
  
  page_penalties[CMP_AX] = 1;
  page_penalties[CMP_AY] = 1;
  page_penalties[CMP_IY] = 1;
  
  page_penalties[EOR_AX] = 1;
  page_penalties[EOR_AY] = 1;
  page_penalties[EOR_IY] = 1;

  page_penalties[LDA_AX] = 1;
  page_penalties[LDA_AY] = 1;
  page_penalties[LDA_IY] = 1;
  
  page_penalties[LDX_AY] = 1;
  
  page_penalties[LDY_AX] = 1;
  
  page_penalties[ORA_AX] = 1;
  page_penalties[ORA_AY] = 1;
  page_penalties[ORA_IY] = 1;
  
  page_penalties[SBC_AX] = 1;
  page_penalties[SBC_AY] = 1;
  page_penalties[SBC_IY] = 1;

}

#endif
