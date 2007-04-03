#include <stdio.h>
#include "NEStypes.h"

#define SET_STATUS_BIT(bit, val) status ^= (-((val) != 0) ^ status) & (1 << bit)

bit_8 status = 0;

int main(){

  SET_STATUS_BIT(0, 1);
  SET_STATUS_BIT(1, 2);
  SET_STATUS_BIT(0, 0);

  printf("%d\n", status);

  return 0;
}
