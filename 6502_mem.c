#include "6502_mem.h"
#include "nes_ppu.h"
#include "NEStypes.h"

#include <assert.h>
#include <stdio.h>

#define MEM_SPACE 65536
#define STACK_BASE 0x0100

bit_8 stack_pointer;

//memory
bit_8 * mem[0x10000];
bit_8 mem_data[0x10000];

int initialized = 0;

void init_mem(){
  //set mem to point to mem_data
  int i;
  for (i = 0; i < 0x10000; i++){
    mem[i] = &mem_data[i];
  }

  stack_pointer = 0xFF;

  //init mem locations 0000 - 0800 with zeros for now
  for (i = 0; i < 0x0800; i++){
    *(mem[i]) = 0;
  }
  
  //init mem locations 0800 - 2000 to mirror 0000 - 0800 three times
  for (i = 0x0800; i < 0x2000; i++){
    mem[i] = mem[i % 0x0800];
  }

  //set I/O registers to zero (2000 - 2007)
  for (i = 0x2000; i < 0x2007; i++){
    *(mem[i]) = 0;
  }
  
  //now mirror those 8 bits through 4020
  for (i = 0x2008; i < 0x4020; i++){
    mem[i] = mem[i % 0x8];
  }

  //zero out expansion rom
  for (i = 0x4020; i < 0x6000; i++){
    *(mem[i]) = 0;
  }

  //zero out SRAM
  for (i = 0x6000; i < 0x8000; i++){
    *(mem[i]) = 0;
  }
  
  //zero out lower bank
  for (i = 0x8000; i < 0xC000; i++){
    *(mem[i]) = 0;
  }

  //zero out upper bank
  for (i = 0xC000; i < 0x10000; i++){
    *(mem[i]) = 0;
  }
  
}

//should maybe not inline when the procedure gets more complex
inline void WRITE(bit_16 address, bit_8 value){
  //for now simply write to the address
  //printf("Writing at address: %x, value: %x\n", address, value);
  if (initialized){
    printf("WRITE address: %x value: %x\n", address, value);
  
    if (address > 0x8000){
      //printf("***WRITE TO ROM\n");
      vromSwitch(address, value);
    }  
  }
  
  *(mem[address]) = value;
}

//should maybe not inline when the procedure gets more complex
inline bit_8 * READ(bit_16 address){
  //for now simply read the value from the address
  return mem[address];
}

inline void PUSH(bit_8 value){
  stack_pointer--;
  printf("pushed, sp: %x\n", stack_pointer);
  *mem[stack_pointer + STACK_BASE] = value;
}

inline bit_8 POP(){
  printf("popped, sp: %x\n", stack_pointer+1);
  return *mem[stack_pointer++ + STACK_BASE];
}
