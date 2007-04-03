#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

#include "6502_mem.h"
#include "6502_debugger.h"
#include "NEStypes.h"
#include "opcodes.h"
#include "6502.h"

#define QUIT "quit"
#define EXIT "exit"
#define NEXT "next"
#define SKIP "skip"
#define OVER "over"
#define VECTOR "vector"
#define A "A"
#define X "X"
#define Y "Y"
#define GPC "PC"
#define GC "GC"
#define GZ "GZ"
#define GI "GI"
#define GD "GD"
#define GB "GB"
#define GV "GV"
#define GN "GN"
#define SP "SP"
#define OP "OP"

extern bit_8 REG_A;
extern bit_8 REG_X;
extern bit_8 REG_Y;
extern bit_16 PCOUNTER;

extern bit_8 status;

extern bit_8 stack_pointer;

#define GET_STATUS_BIT(bit) (status & (0x1 << bit)) >> bit

#define G_C GET_STATUS_BIT(0)
#define G_Z GET_STATUS_BIT(1)
#define G_I GET_STATUS_BIT(2)
#define G_D GET_STATUS_BIT(3)
#define G_B GET_STATUS_BIT(4)
#define G_V GET_STATUS_BIT(6)
#define G_N GET_STATUS_BIT(7)

char *opcode_text[0xFF];
int debugger_initialized = 0;

extern instruction curInst;

int quit = 0;
int skip = 0;
int toSkip = 30;
int jOver = 0;
int lastPC;

void start_debugger(options *procOptions){

  if (!debugger_initialized){
    init_debugger();
    debugger_initialized = 1;
  }

  if (procOptions->disassemble){
    printf("%x: %s\n", PCOUNTER, opcode_text[curInst.realOpcode]);
    return;
  }

  if (skip){
    toSkip--;
    if (toSkip <= 0){
      toSkip = 30;
      skip = 0;
    }
    return;
  }

  if (jOver && PCOUNTER < (lastPC + 5) && PCOUNTER > lastPC ){
    jOver = 0;
  } 
  else if (jOver){
    return;
  }

  char *input;
  while (!quit){
    input = readline("Enter value: ");
    
    if (!strcmp(QUIT, input)){
      quit = 1;
      break;
    }
    else if (!strcmp(NEXT, input)){
      break;
    }
    else if (!strcmp(OVER, input)){
      jOver = 1;
      lastPC = PCOUNTER;
      break;
    }
    else if (!strcmp(SKIP, input)){
      skip = 1;
      break;
    }
    else if (!strcmp(EXIT, input)){
      exit(0);
    }
    else if (!strcmp(VECTOR, input)){
      int i;
      for (i = 0xfffa; i <= 0xffff ; i++){
	printf("%x\n", *READ(i));
      }
    }
    else if (!strcmp(A, input)){
      printf("A: %x\n", REG_A);
    }
    else if (!strcmp(X, input)){
      printf("X: %x\n", REG_X);
    }
    else if (!strcmp(Y, input)){
      printf("Y: %x\n", REG_Y);
    }
    else if (!strcmp(GPC, input)){
      printf("PC: %x\n", PCOUNTER);
    }
    else if (!strcmp(GC, input)){
      printf("C: %d\n", G_C);
    }
    else if (!strcmp(GZ, input)){
      printf("Z: %d\n", G_Z);
    }
    else if (!strcmp(GI, input)){
      printf("I: %d\n", G_I);
    }
    else if (!strcmp(GD, input)){
      printf("D: %d\n", G_D);
    }
    else if (!strcmp(GB, input)){
      printf("B: %d\n", G_B);
    }
    else if (!strcmp(GV, input)){
      printf("V: %d\n", G_V);
    }
    else if (!strcmp(GN, input)){
      printf("N: %d\n", G_N);
    }
    else if (!strcmp(SP, input)){
      printf("SP: %x\n", stack_pointer);
    }
    else if (!strcmp(OP, input)){
      printf("OP: %s\n", opcode_text[curInst.realOpcode]);
    }
    else {
      printf("MEM: %x\n", *READ(strtol(input, NULL, 16)));
    }

    free(input);
  }

}

void init_debugger(){

  opcode_text[ADC_I] = "ADC_I";
  opcode_text[ADC_Z] = "ADC_Z";
  opcode_text[ADC_ZX] = "ADC_ZX";
  opcode_text[ADC_A] = "ADC_A";
  opcode_text[ADC_AX] = "ADC_AX";
  opcode_text[ADC_AY] = "ADC_AY";
  opcode_text[ADC_IX] = "ADC_IX";
  opcode_text[ADC_IY] = "ADC_IY";

  opcode_text[AND_I] = "AND_I";
  opcode_text[AND_Z] = "AND_Z";
  opcode_text[AND_ZX] = "AND_ZX";
  opcode_text[AND_A] = "AND_A";
  opcode_text[AND_AX] = "AND_AX";
  opcode_text[AND_AY] = "AND_AY";
  opcode_text[AND_IX] = "AND_IX";
  opcode_text[AND_IY] = "AND_IY";

  opcode_text[ASL_IM] = "ASL_IM";
  opcode_text[ASL_Z] = "ASL_Z";
  opcode_text[ASL_ZX] = "ASL_ZX";
  opcode_text[ASL_A] = "ASL_A";
  opcode_text[ASL_AX] = "ASL_AX";

  opcode_text[BCC_I] = "BCC_I";
  opcode_text[BCS_I] = "BCS_I";
  opcode_text[BEQ_I] = "BEQ_I";

  opcode_text[BIT_Z] = "BIT_Z";
  opcode_text[BIT_A] = "BIT_A";

  opcode_text[BMI_I] = "BMI_I";
  opcode_text[BNE_I] = "BNE_I";
  opcode_text[BPL_I] = "BPL_I";

  opcode_text[BRK_IM] = "BRK_IM";

  opcode_text[BVC_I] = "BVC_I";
  opcode_text[BVS_I] = "BVS_I";

  opcode_text[CLC_IM] = "CLC_IM";
  opcode_text[CLD_IM] = "CLD_IM";
  opcode_text[CLI_IM] = "CLI_IM";
  opcode_text[CLV_IM] = "CLV_IM";

  opcode_text[CMP_I] = "CMP_I";
  opcode_text[CMP_Z] = "CMP_Z";
  opcode_text[CMP_ZX] = "CMP_ZX";
  opcode_text[CMP_A] = "CMP_A";
  opcode_text[CMP_AX] = "CMP_AX";
  opcode_text[CMP_AY] = "CMP_AY";
  opcode_text[CMP_IX] = "CMP_IX";
  opcode_text[CMP_IY] = "CMP_IY";

  opcode_text[CPX_I] = "CPX_I";
  opcode_text[CPX_Z] = "CPX_Z";
  opcode_text[CPX_A] = "CPX_A";

  opcode_text[CPY_I] = "CPY_I";
  opcode_text[CPY_Z] = "CPY_Z";
  opcode_text[CPY_A] = "CPY_A";

  opcode_text[DEC_Z] = "DEC_Z";
  opcode_text[DEC_ZX] = "DEC_ZX";
  opcode_text[DEC_A] = "DEC_A";
  opcode_text[DEC_AX] = "DEC_AX";

  opcode_text[DEX_IM] = "DEX_IM";
  opcode_text[DEY_IM] = "DEY_IM";

  opcode_text[EOR_I] = "EOR_I";
  opcode_text[EOR_Z] = "EOR_Z";
  opcode_text[EOR_ZX] = "EOR_ZX";
  opcode_text[EOR_A] = "EOR_A";
  opcode_text[EOR_AX] = "EOR_AX";
  opcode_text[EOR_AY] = "EOR_AY";
  opcode_text[EOR_IX] = "EOR_IX";
  opcode_text[EOR_IY] = "EOR_IY";

  opcode_text[INC_Z] = "INC_Z";
  opcode_text[INC_ZX] = "INC_ZX";
  opcode_text[INC_A] = "INC_A";
  opcode_text[INC_AX] = "INC_AX";

  opcode_text[INX_IM] = "INX_IM";
  opcode_text[INY_IM] = "INY_IM";

  opcode_text[JMP_A] = "JMP_A";
  opcode_text[JMP_IN] = "JMP_IN";

  opcode_text[JSR_A] = "JSR_A";

  opcode_text[LDA_I] = "LDA_I";
  opcode_text[LDA_Z] = "LDA_Z";
  opcode_text[LDA_ZX] = "LDA_ZX";
  opcode_text[LDA_A] = "LDA_A";
  opcode_text[LDA_AX] = "LDA_AX";
  opcode_text[LDA_AY] = "LDA_AY";
  opcode_text[LDA_IX] = "LDA_IX";
  opcode_text[LDA_IY] = "LDA_IY";

  opcode_text[LDX_I] = "LDX_I";
  opcode_text[LDX_Z] = "LDX_Z";
  opcode_text[LDX_ZY] = "LDX_ZY";
  opcode_text[LDX_A] = "LDX_A";
  opcode_text[LDX_AY] = "LDX_AY";

  opcode_text[LDY_I] = "LDY_I";
  opcode_text[LDY_Z] = "LDY_Z";
  opcode_text[LDY_ZX] = "LDY_ZX";
  opcode_text[LDY_A] = "LDY_A";
  opcode_text[LDY_AX] = "LDY_AX";

  opcode_text[LSR_AC] = "LSR_AC";
  opcode_text[LSR_Z] = "LSR_Z";
  opcode_text[LSR_ZX] = "LSR_ZX";
  opcode_text[LSR_A] = "LSR_A";
  opcode_text[LSR_AX] = "LSR_AX";

  opcode_text[NOP_IM] = "NOP_IM";

  opcode_text[ORA_I] = "ORA_I";
  opcode_text[ORA_Z] = "ORA_Z";
  opcode_text[ORA_ZX] = "ORA_ZX";
  opcode_text[ORA_A] = "ORA_A";
  opcode_text[ORA_AX] = "ORA_AX";
  opcode_text[ORA_AY] = "ORA_AY";
  opcode_text[ORA_IX] = "ORA_IX";
  opcode_text[ORA_IY] = "ORA_IY";

  opcode_text[PHA_IM] = "PHA_IM";
  opcode_text[PHP_IM] = "PHP_IM";

  opcode_text[PLA_IM] = "PLA_IM";
  opcode_text[PLP_IM] = "PLP_IM";

  opcode_text[ROL_AC] = "ROL_AC";
  opcode_text[ROL_Z] = "ROL_Z";
  opcode_text[ROL_ZX] = "ROL_ZX";
  opcode_text[ROL_A] = "ROL_A";
  opcode_text[ROL_AX] = "ROL_AX";

  opcode_text[ROR_AC] = "ROR_AC";
  opcode_text[ROR_Z] = "ROR_Z";
  opcode_text[ROR_ZX] = "ROR_ZX";
  opcode_text[ROR_A] = "ROR_A";
  opcode_text[ROR_AX] = "ROR_AX";

  opcode_text[RTI_IM] = "RTI_IM";
  opcode_text[RTS_IM] = "RTS_IM";

  opcode_text[SBC_I] = "SBC_I";
  opcode_text[SBC_Z] = "SBC_Z";
  opcode_text[SBC_ZX] = "SBC_ZX";
  opcode_text[SBC_A] = "SBC_A";
  opcode_text[SBC_AX] = "SBC_AX";
  opcode_text[SBC_AY] = "SBC_AY";
  opcode_text[SBC_IX] = "SBC_IX";
  opcode_text[SBC_IY] = "SBC_IY";

  opcode_text[SEC_IM] = "SEC_IM";
  opcode_text[SED_IM] = "SED_IM";
  opcode_text[SEI_IM] = "SEI_IM";

  opcode_text[STA_Z] = "STA_Z";
  opcode_text[STA_ZX] = "STA_ZX";
  opcode_text[STA_A] = "STA_A";
  opcode_text[STA_AX] = "STA_AX";
  opcode_text[STA_AY] = "STA_AY";
  opcode_text[STA_IX] = "STA_IX";
  opcode_text[STA_IY] = "STA_IY";

  opcode_text[STX_Z] = "STX_Z";
  opcode_text[STX_ZY] = "STX_ZY";
  opcode_text[STX_A] = "STX_A";

  opcode_text[STY_Z] = "STY_Z";
  opcode_text[STY_ZY] = "STY_ZY";
  opcode_text[STY_A] = "STY_A";

  opcode_text[TAX_IM] = "TAX_IM";
  opcode_text[TAY_IM] = "TAY_IM";

  opcode_text[TSX_IM] = "TSX_IM";
  opcode_text[TXA_IM] = "TXA_IM";
  opcode_text[TXS_IM] = "TXS_IM";
  opcode_text[TYA_IM] = "TYA_IM";

}
