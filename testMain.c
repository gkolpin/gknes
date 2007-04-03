#include "opcode_map.h"

int main(){

  initOpcodeMap();
  printf("%x\n", opcode_map[SED_IM]);

  return 0;
}
