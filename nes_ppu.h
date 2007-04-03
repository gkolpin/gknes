#ifndef NES_PPU_H
#define NES_PPU_H

#include "NEStypes.h"

void vromSwitch(bit_16 address, bit_8 value);
void setVrom(bit_8 *buf, int length);

#endif
