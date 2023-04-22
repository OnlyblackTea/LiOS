#include <stdint.h>

#define UART        0x10000000
#define UART_THR    (uint8_t*)(UART+0x00)
#define UART_LSR    (uint8_t*)(UART+0x05)
#define UART_LSR_EMPTY_MASK 0x40

int _kputc(char ch)
{
  while((*UART_LSR & UART_LSR_EMPTY_MASK) == 0);
  return *(UART_THR) = ch;
}

void _kputs(char *s)
{
  while(*s)
    _kputc(*s++);
}

void kernel_main()
{
  _kputs("HELLO OS!\n");
  while(1);
  return 0;
}