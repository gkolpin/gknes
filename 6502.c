#include "opcodes.h"
#include "NEStypes.h"
#include "6502_mem.h"
#include "opcode_map.h"
#include "6502.h"
#include "6502_debugger.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_8_BIT 255

bit_8 REG_A = 0;
bit_8 REG_X = 0;
bit_8 REG_Y = 0;
bit_16 PCOUNTER = 0;

bit_8 status = 0x20; // bit 5 supposed to be logical one always

unsigned long long cycles = 0;

extern bit_8 stack_pointer; //defined in 6502_mem.c

options *procOptions;

#define SET_STATUS_BIT(bit, val) status ^= (-((val) != 0) ^ status) & (1 << bit)

#define GET_STATUS_BIT(bit) (status & (0x1 << bit)) >> bit

#define S_C(val) SET_STATUS_BIT(0, val)
#define S_Z(val) SET_STATUS_BIT(1, val)
#define S_I(val) SET_STATUS_BIT(2, val)
#define S_D(val) SET_STATUS_BIT(3, val)
#define S_B(val) SET_STATUS_BIT(4, val)
#define S_V(val) SET_STATUS_BIT(6, val)
#define S_N(val) SET_STATUS_BIT(7, val)

#define G_C GET_STATUS_BIT(0)
#define G_Z GET_STATUS_BIT(1)
#define G_I GET_STATUS_BIT(2)
#define G_D GET_STATUS_BIT(3)
#define G_B GET_STATUS_BIT(4)
#define G_V GET_STATUS_BIT(6)
#define G_N GET_STATUS_BIT(7)

instruction curInst;

void startProcessor(options *pOptions){
  procOptions = pOptions;

  //init opcode map
  initOpcodeMap();

  //set PCOUNTER to reset address: FFFC and FFFD
  PCOUNTER = ((bit_16)*READ(0xFFFD)) << 8;
  PCOUNTER |= (*READ(0xFFFC) & 0xFF);

  printf("%x\n", *READ(0xFFFD));
  printf("%x\n", *READ(0xFFFC));
  printf("%x\n", PCOUNTER);

  while (1){
    getNextInstruction();
    executeInstruction(&curInst);
  }
}

void getNextInstruction(){
  bit_8 opcode = *READ(PCOUNTER);
  curInst.realOpcode = opcode;
  curInst.opcode16 = GET_OP16(opcode);
  curInst.cycles = cycle_map[opcode];

  bit_16 temp16;

  start_debugger(procOptions);

  //now figure out the operand
  switch (GET_OP16_TYPE(curInst.opcode16)){
  case HEXIFY_N(I):
    curInst.operand = READ(PCOUNTER+1);
    PCOUNTER += 2;
    break;
  case HEXIFY_N(Z):
    curInst.address = *READ(PCOUNTER+1);
    curInst.operand = READ(curInst.address);
    PCOUNTER += 2;
    break;
  case HEXIFY_N(ZX):
    curInst.address = (*READ(PCOUNTER+1) + REG_X) & 0xFF;
    curInst.operand = 
      READ(curInst.address);
    PCOUNTER += 2;
    break;
  case HEXIFY_N(ZY):
    curInst.address = (*READ(PCOUNTER+1) + REG_Y) & 0xFF;
    curInst.operand = 
      READ(curInst.address);
    PCOUNTER += 2;
    break;
  case HEXIFY_N(A):
    temp16 = *READ(PCOUNTER+2);
    curInst.operand = 
      READ((temp16 << 8) + *READ(PCOUNTER+1));
    curInst.address = (temp16 << 8) + *READ(PCOUNTER+1);
    PCOUNTER += 3;
    break;
  case HEXIFY_N(AX):
    temp16 = *READ(PCOUNTER+2);
    curInst.address = ((temp16 << 8) + *READ(PCOUNTER+1) + REG_X)
      & 0xFFFF;
    curInst.operand = READ(curInst.address);
    PCOUNTER += 3;
    break;
  case HEXIFY_N(AY):
    temp16 = *READ(PCOUNTER+2);
    curInst.address = ((temp16 << 8) + *READ(PCOUNTER+1) + REG_Y) 
      & 0xFFFF;
    curInst.operand = READ(curInst.address);
    PCOUNTER += 3;
    break;
  case HEXIFY_N(IX):
    //get address of 16 bit pointer
    temp16 = *READ(PCOUNTER+1);
    curInst.operand = 
      READ((temp16 + REG_X) & 0xFF);
    //load 16 bit pointer into temp
    temp16 = *READ(*curInst.operand + 1) << 8;
    temp16 += *READ(*curInst.operand);
    curInst.operand = READ(temp16);
    curInst.address = temp16;
    PCOUNTER += 2;
    break;
  case HEXIFY_N(IY):
    //get address of 16 bit pointer
    temp16 = *READ(PCOUNTER+1);
    curInst.operand = READ(temp16);
    //load 16 bit pointer into temp
    temp16 = *READ(*curInst.operand + 1) << 8;
    temp16 += *READ(*curInst.operand);
    temp16 += REG_Y;
    curInst.operand = READ(temp16);
    curInst.address = temp16;
    PCOUNTER += 2;
    break;
  case HEXIFY_N(IM):
    PCOUNTER += 1;
    break;
  case HEXIFY_N(IN):
    temp16 = *READ(PCOUNTER+1) << 8;
    temp16 += *READ(PCOUNTER);
    curInst.address = *READ(temp16 + 1) << 8;
    curInst.address += *READ(temp16);
    PCOUNTER += 3;
    break;
  case HEXIFY_N(AC):
    curInst.operand = &REG_A;
    PCOUNTER += 1;
    break;
  default:
    assert(0);
    break;
  }

  //now determine if address is a page boundary, increment cycles
  //according to page_penalties table

  curInst.cycles += (page_penalties[curInst.realOpcode] -
		     (curInst.address ^ 0xFF));
  
}

inline void updateCyclesForBranch(signed_bit_8 offset){
  cycles++;
  cycles += (PCOUNTER % 0xFF) == ((PCOUNTER + (signed_bit_8)offset) % 0xFF) ? 0 : 1;
}

inline bit_8 * getOperand(instruction *inst){
  return inst->operand;
}
inline bit_16 getAddress(instruction *inst){
  return inst->address;
}

void executeInstruction(instruction *inst){

  register bit_16 op_16;
  register bit_16 temp_16;
  bit_8 * operand_8;

  unsigned int temp32bit;
  
  /*printf("real opcode: %x\n", inst->realOpcode);
  printf("opcode class: %x\n", GET_OP16_CLASS(inst->opcode16));
  printf("opcode type: %x\n", GET_OP16_TYPE(inst->opcode16));
  printf("address: %x\n", getAddress(inst));
  printf("operand: %x\n", getOperand(inst) == 0 ? 0 : getOperand(inst)[0]);
  printf("0x69: %x\n\n", *READ(0x79));*/

  switch(GET_OP16_CLASS(inst->opcode16)){
    
  case HEXIFY_N(ADC): {
    op_16 = *getOperand(inst);
    
    temp_16 = REG_A + op_16 + G_C;
    
    S_Z(REG_A == 0 ? 1 : 0);
    //S_Z(1);
    S_N(REG_A & 0x80);

    S_C(temp_16 > MAX_8_BIT);
    
    S_V(((op_16 ^ temp_16) & 0x80) && ((REG_A ^ temp_16) & 0x80));
    
    REG_A = (bit_8)temp_16;
    
    break;
  }
    
  case HEXIFY_N(AND): {
    
    op_16 = *getOperand(inst);
    
    REG_A = REG_A & op_16;

    S_N(0x80 & REG_A);
    S_Z(REG_A == 0 ? 1 : 0);

    break;
  }
   
  case HEXIFY_N(ASL): {

    operand_8 = getOperand(inst);
    
    S_C(*operand_8 & 0x80);
    
    *operand_8 <<= 1;
    //REG_A &= 0xff;
    
    S_Z(*operand_8 == 0);
    S_N(0x80 & *operand_8);

    break;
  }

  case HEXIFY_N(BCC): {
    if (!G_C){

      updateCyclesForBranch(*getOperand(inst));

      op_16 = *getOperand(inst);
      PCOUNTER += (signed_bit_8)op_16;
    }
   
    break;
  }
    
  case HEXIFY_N(BCS): {
    if (G_C){

      updateCyclesForBranch(*getOperand(inst));

      op_16 = *getOperand(inst);
      PCOUNTER += (signed_bit_8)op_16;
    }

    break;
  }

  case HEXIFY_N(BEQ): {
    if (G_Z){

      updateCyclesForBranch(*getOperand(inst));

      op_16 = *getOperand(inst);
      PCOUNTER += (signed_bit_8)op_16;
    }

    break;
  }

  case HEXIFY_N(BIT): {
    op_16 = *getOperand(inst);
    
    temp_16 = REG_A & op_16;
    
    S_Z(!temp_16);
    S_V(temp_16 & 0x40);
    S_N(temp_16 & 0x80);

    break;
  }

  case HEXIFY_N(BMI): {
    if (G_N){

      updateCyclesForBranch(*getOperand(inst));

      op_16 = *getOperand(inst);
      PCOUNTER += (signed_bit_8)op_16;
    }

    break;
  }
    
  case HEXIFY_N(BNE): {
    if (!G_Z){

      updateCyclesForBranch(*getOperand(inst));

      op_16 = *getOperand(inst);
      PCOUNTER += (signed_bit_8)op_16;
    }

    break;
  }

  case HEXIFY_N(BPL): {
    if (!G_N){

      updateCyclesForBranch(*getOperand(inst));

      op_16 = *getOperand(inst);
      PCOUNTER += (signed_bit_8)op_16;
    }

    break;
  }

  case HEXIFY_N(BRK): {
    printf("BRK\n");
    
    //@TODO - make sure interrupts are handled correctly

    PUSH((PCOUNTER >> 8) & 0xFF);
    PUSH(PCOUNTER & 0xFF);
    PUSH(status);

    PCOUNTER = *READ(0xFFFF) << 8;
    PCOUNTER |= (*READ(0xFFFE) & 0xFF);

    S_B(1);

    break;
  }

  case HEXIFY_N(BVC): {
    if (!G_V){

      updateCyclesForBranch(*getOperand(inst));

      op_16 = *getOperand(inst);
      PCOUNTER += (signed_bit_8)op_16;
    }

    break;
  }

  case HEXIFY_N(BVS): {
    if (G_V){

      updateCyclesForBranch(*getOperand(inst));

      op_16 = *getOperand(inst);
      PCOUNTER += (signed_bit_8)op_16;
    }

    break;
  }

  case HEXIFY_N(CLC): {

    S_C(0);

    break;
  }

  case HEXIFY_N(CLD): {

    S_D(0);

    break;
  }

  case HEXIFY_N(CLI): {

    S_I(0);

    break;
  }

  case HEXIFY_N(CLV): {

    S_V(0);

    break;
  }

  case HEXIFY_N(CMP): {

    op_16 = *getOperand(inst);

    temp_16 = REG_A - op_16;

    S_C(REG_A >= op_16);
    
    S_Z(REG_A == op_16);
    
    S_N(temp_16 & 0x80);

    break;
  }

  case HEXIFY_N(CPX): {

    op_16 = *getOperand(inst);
    
    temp_16 = REG_X - op_16;
    
    S_C(REG_X >= op_16);
    S_Z(REG_X == op_16);
    S_N(temp_16 & 0x80);

    break;
  }

  case HEXIFY_N(CPY): {

    op_16 = *getOperand(inst);
    
    temp_16 = REG_Y - op_16;
    
    S_C(REG_Y >= op_16);
    S_Z(REG_Y == op_16);
    S_N(temp_16 & 0x80);

    break;
  }

  case HEXIFY_N(DEC): {

    operand_8 = getOperand(inst);
    
    *operand_8--;
    
    S_Z(*operand_8 == 0);
    S_N(*operand_8 & 0x80);

    break;
  }

  case HEXIFY_N(DEX): {
    
    REG_X--;
    
    S_Z(REG_X == 0);
    S_N(REG_X & 0x80);
    
    break;
  }

  case HEXIFY_N(DEY): {

    REG_Y--;
    
    S_Z(REG_Y == 0);
    S_N(REG_Y & 0x80);

    break;
  }

  case HEXIFY_N(EOR): {

    op_16 = *getOperand(inst);

    temp_16 = REG_A ^ op_16;
    REG_A = temp_16;

    S_Z(temp_16 == 0);
    S_N(temp_16 & 0x80);
    
    break;
  }

  case HEXIFY_N(INC): {

    operand_8 = getOperand(inst);

    *operand_8++;
    
    S_Z(*operand_8 == 0);
    S_N(*operand_8 & 0x80);

    break;
  }

  case HEXIFY_N(INX): {

    REG_X++;
    
    S_Z(REG_X == 0);
    S_N(REG_X & 0x80);
    
    break;
  }

  case HEXIFY_N(INY): {
    REG_Y++;
    
    S_Z(REG_Y == 0);
    S_N(REG_Y & 0x80);

    break;
  }

  case HEXIFY_N(JMP): {

    PCOUNTER = getAddress(inst);
    
    break;
  }
    
  case HEXIFY_N(JSR): {
    temp_16 = PCOUNTER - 1;
    PUSH((temp_16 >> 8) & 0xFF);
    PUSH(temp_16 & 0xFF);
    
    PCOUNTER = getAddress(inst);

    break;
  }

  case HEXIFY_N(LDA): {

    REG_A = *getOperand(inst);

    S_Z(REG_A == 0);
    S_N(REG_A & 0x80);

    break;
  }

  case HEXIFY_N(LDX): {

    REG_X = *getOperand(inst);

    S_Z(REG_X == 0);
    S_N(REG_X & 0x80);

    break;
  }

  case HEXIFY_N(LDY): {
    
    REG_Y = *getOperand(inst);
    
    S_Z(REG_Y == 0);
    S_N(REG_Y & 0x80);
    
    break;
  }

  case HEXIFY_N(LSR): {

    operand_8 = getOperand(inst);

    S_C(*operand_8 & 0x1);

    *operand_8 >>= 1;

    S_Z(*operand_8 == 0);
    S_N(*operand_8 & 0x80);

    break;
  }

  case HEXIFY_N(NOP): {

    //do nothing, except increment program counter
    PCOUNTER++;
    
    break;
  }

  case HEXIFY_N(ORA): {

    op_16 = *getOperand(inst);
    
    REG_A |= op_16;

    S_Z(REG_A == 0);
    S_N(REG_A & 0x80);

    break;
  }

  case HEXIFY_N(PHA): {

    //push accumulator on the stack
    PUSH(REG_A);

    break;
  }

  case HEXIFY_N(PHP): {

    //pushes copy of the status flags on the stack
    PUSH(status);

    break;
  }

  case HEXIFY_N(PLA): {

    REG_A = POP();

    S_Z(REG_A == 0);
    S_N(REG_A & 0x80);
    
    break;
  }

  case HEXIFY_N(PLP): {

    // set status flags from value pulled from stack
    status = POP();
    
    break;
  }

  case HEXIFY_N(ROL): {

    operand_8 = getOperand(inst);

    *operand_8 <<= 1;

    S_C(*operand_8 & 0x80);
    S_Z(REG_A == 0); //??
    S_N(*operand_8 & 0x80);
    
    break;
  }

  case HEXIFY_N(ROR): {

    operand_8 = getOperand(inst);

    *operand_8 >>= 1;

    S_C(*operand_8 & 0x80);
    S_Z(REG_A == 0); //??
    S_N(*operand_8 & 0x80);
    
    break;
  }

  case HEXIFY_N(RTI): {

    status = POP();
    PCOUNTER = POP() & 0xFF;
    PCOUNTER |= (POP() << 8);
    
    break;
  }

  case HEXIFY_N(RTS): {
    //printf("sp: %x\n", stack_pointer);

    //status = POP(); -status not pushed
    PCOUNTER = POP() & 0xFF;
    PCOUNTER |= (POP() << 8);
    PCOUNTER++;
    
    break;
  }

  case HEXIFY_N(SBC): {

    op_16 = *getOperand(inst);

    temp_16 = REG_A - op_16 - (1 - G_C);
    
    S_Z(REG_A == 0);
    S_N(REG_A & 0x80);
    
    S_V(((op_16 ^ temp_16) & 0x80) && ((REG_A ^ temp_16) & 0x80));

    //V(((temp <= 0x7f && op_16 <= 0x7f) && (0x80 & A)) ||
    //((temp > 0x7f && op_16 > 0x7f) && (0x80 & REG_A == 0)));    
    
    S_C(temp_16 & 0x8000);

    REG_A = temp_16 & 0xFF;

    break;
  }

  case HEXIFY_N(SEC): {

    S_C(1);
    
    break;
  }
    
  case HEXIFY_N(SED): {

    S_D(1);

    break;
  }

  case HEXIFY_N(SEI): {
    
    S_I(1);
    
    break;
  }

  case HEXIFY_N(STA): {

    //store acc to memory
    op_16 = getAddress(inst);
    WRITE(op_16, REG_A);
    
    break;
  }

  case HEXIFY_N(STX): {

    //store the REG_X into memory
    op_16 = getAddress(inst);
    WRITE(op_16, REG_X);
    
    break;
  }

  case HEXIFY_N(STY): {

    //store the Y into memory
    op_16 = getAddress(inst);
    WRITE(op_16, REG_Y);
    
    break;
  }

  case HEXIFY_N(TAX): {

    REG_X = REG_A;
    
    S_Z(REG_X);
    S_N(REG_X & 0x80);

    break;
  }

  case HEXIFY_N(TAY): {

    REG_Y = REG_A;
    
    S_Z(REG_Y);
    S_N(REG_Y & 0x80);

    break;
  }

  case HEXIFY_N(TSX): {

    REG_X = stack_pointer;

    S_Z(REG_X == 0);
    S_N(REG_X & 0x80);

    break;
  }

  case HEXIFY_N(TXA): {

    REG_A = REG_X;
    
    S_Z(REG_A == 0);
    S_N(REG_A & 0x80);

    break;
  }

  case HEXIFY_N(TXS): {

    stack_pointer = REG_X;
    
    break;
  }
    
  case HEXIFY_N(TYA): {

    REG_A = REG_Y;
    
    S_Z(REG_A == 0);
    S_N(REG_A & 0x80);

    break;
  }
  default: {
    assert(0);
    break;
  }

  }

}
