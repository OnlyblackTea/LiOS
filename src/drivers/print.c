#include "print.h"
#include "uart.h"

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
