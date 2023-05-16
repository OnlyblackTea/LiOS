#include "os.h"

int kernel_main()
{
  ecall_puts("HELLO OS!\n");
  while(1);
  return 0;
}