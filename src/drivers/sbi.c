#include <stdint.h>
#include "sbi.h"

/**
 * @brief 
 * Anything about this file please refer to docs/sbi.md
 */
const unsigned long SBI_SET_TIMER = 0;
const unsigned long SBI_CONSOLE_PUTCHAR = 1;
const unsigned long SBI_CONSOLE_GETCHAR = 2;
const unsigned long SBI_CLEAR_IPI = 3;
const unsigned long SBI_SEND_IPI = 4;
const unsigned long SBI_REMOTE_FENCE_I = 5;
const unsigned long SBI_REMOTE_SFENCE_VMA = 6;
const unsigned long SBI_REMOTE_SFENCE_VMA_ASID = 7;
const unsigned long SBI_SHUTDOWN = 8;


unsigned long k_sbi_call(unsigned long which, unsigned long arg0, 
                unsigned long arg1, unsigned long arg2)
{
  register unsigned long a0 asm("a0") = arg0; 
  register unsigned long a1 asm("a1") = arg1; 
  register unsigned long a2 asm("a2") = arg2;
  register unsigned long a7 asm("a7") = which; 
  asm volatile("ecall"
    : "+r"(a0)
    : "r" (a1), "r"(a2), "r"(a7)
    : "memory" 
  );
  return a0;
}

void ecall_putchar(unsigned long c)
{
  k_sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}

unsigned long ecall_getchar()
{
  return k_sbi_call(SBI_CONSOLE_GETCHAR, 0, 0, 0);
}

void ecall_shutdown()
{
  k_sbi_call(SBI_SHUTDOWN, 0, 0, 0);
}