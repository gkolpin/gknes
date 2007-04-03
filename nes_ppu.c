#include "NEStypes.h"
#include "nes_ppu.h"

#include <assert.h>

bit_8 ram[0x4000]; //PPU has 16kb of memory
bit_8 spr_ram[0xFF]; //256 bytes of sprite ram

#define R2000 0
#define R2001 1
#define R2002 2
#define R2003 3
#define R2004 4
#define R2005 5
#define R2006 6
#define R2007 7

#define GET_BIT_VALUE(reg, bit) (reg & (0x1 << bit)) >> bit

bit_8 registers[8]; //8 registers: $2000 - $2007

bit_16 curAddress;
int upperAddressBits = 1;

int vromBanks;
bit_8 vrom[4][8192];
bit_8 *curVrom;

void init_ppumem();
void setRegister(int reg, bit_8 value);

void init_ppu(){
  init_ppumem();
}

void init_ppumem(){
  //zero out ram
  int i;
  for (i = 0; i < 0x4000; i++){
    ram[i] = 0;
  }

  //zero out sprite ram
  for (i = 0; i < 0xFF; i++){
    spr_ram[i] = 0;
  }

  //zero out registers
  for (i = 0; i < 8; i++){
    registers[i] = 0;
  }
}

inline void setRegister(int reg, bit_8 value){
  registers[reg] = value;

  switch (reg){
  case R2000: {
    break;
  }
  case R2001: {
    break;
  }
  case R2002: {
    break;
  }
  case R2003: {
    break;
  }
  case R2004: {
    break;
  }
  case R2005: {
    break;
  }
  case R2006: {
    if (upperAddressBits){
      curAddress = ((bit_16)value) << 8;
      upperAddressBits = 0;
    }
    else {
      curAddress |= value;
      upperAddressBits = 1;
    }
    break;
  }
  case R2007: {
    //@TODO finish 2007 reading
    ram[curAddress] = value;
    if (GET_BIT_VALUE(registers[R2000], 2)){
      curAddress += 32;
    }
    else {
      curAddress += 1;
    }
    break;
  }
  }
}

//for now, hardcode cnrom mapper
void vromSwitch(bit_16 address, bit_8 value){
  if (value > (1 << 7)){
    //vrom 1
    curVrom = vrom[0];
  }
  else if (value > (1 << 6)){
    //vrom 2
    curVrom = vrom[1];
  }
  else if (value > (1 << 5)){
    //vrom 3
    curVrom = vrom[2];
  }
  else if (value > (1 << 4)){
    //vrom 4
    curVrom = vrom[3];
  }
  else {
    assert(0);
  }
}

void setVrom(bit_8 *buf, int length){
  //vrom = (**bit_8)malloc(sizeof(bit_8*) * 4);
  int i;
  for (i = 0; i < 8192 * 4; i++){
    vrom[i / 8192][i % 8192] = buf[i];
  }
  curVrom = vrom[0];
}
