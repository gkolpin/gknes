#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void main(int argc, char **argv){
  unsigned char buf[32768];
  int fd = open(argv[1], O_RDONLY);
  read(fd, buf, 16);
  
  read(fd, buf, 32768);

  int i, j;

  for (i = 0, j = 0x8000; j < 0x10000; i++, j++){
    printf("%x: %x\n", j, buf[i]);
  }

}
