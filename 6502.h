#ifndef NES_6502_H
#define NES_6502_H

#include "NEStypes.h"

typedef struct instruction {
  bit_8 realOpcode;
  bit_16 opcode16;
  bit_16 address;
  bit_8 *operand;
  unsigned short cycles;
} instruction;

void startProcessor();
void getNextInstruction();
void executeInstruction(instruction *inst);

#endif
