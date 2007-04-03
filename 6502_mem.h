#ifndef MEM_H
#define MEM_H

#include "NEStypes.h"

void init_mem();
void WRITE(bit_16 address, bit_8 value);
bit_8 * READ(bit_16 address);

void PUSH(bit_8 value);
bit_8 POP();

#endif
