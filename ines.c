#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "6502_mem.h"
#include "nes_ppu.h"

extern initialized;

//for now hardcode rom loading for john elway's quarterback
void load_rom(char *ines_file){
  unsigned char buf[32768];
  int fd = open(ines_file, O_RDONLY);
  read(fd, buf, 16);
  
  read(fd, buf, 32768);

  int i, j;

  for (i = 0, j = 0x8000; j < 0x10000; i++, j++){
    WRITE(j, buf[i]);
  }

  //JEF has 4 8kb vrom banks after the regular rom
  read(fd, buf, 32768);
  setVrom(buf, 32768);

  close(fd);

  initialized = 1;

}
