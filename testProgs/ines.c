#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main(){
  unsigned char buf[853];
  int fd = open("test.nes", O_RDONLY);
  read(fd, buf, 853);
  
  int i;

  for (i = 0; i < 3; i++){
    printf("%c", buf[i]);
  }
  printf("\n");

  for (i = 0; i < 853; i++){
    printf("%d  %x\n", i, buf[i]);
  }
  return 0;
}
