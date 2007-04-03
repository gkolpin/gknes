#include <stdlib.h>
#include <string.h>

#include "6502_mem.h"
#include "ines.h"
#include "6502.h"
#include "NEStypes.h"

#define DISASSEMBLE "-d"

options * handleArgs(int, char**);

int main(int argc, char **argv){

  options *procOptions = handleArgs(argc, argv);

  //initialize memory
  init_mem();

  //init ppu
  init_ppu();

  //load rom
  load_rom(procOptions->fileName);
  
  //start processor
  startProcessor(procOptions);

  return 0;
}

options * handleArgs(int argc, char **argv){
  options *returnOptions = (options*)malloc(sizeof(options));
  int i;
  char *curArg;
  for (i = 1, curArg = argv[i]; i < argc; i++, curArg = argv[i]){
    if (!strcmp(DISASSEMBLE, curArg)){
      returnOptions->disassemble = 1;
    }
    else {
      returnOptions->fileName = curArg;
    }
  }
  
  return returnOptions;
}
