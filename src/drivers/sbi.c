#include "sbi.h"

uint64_t k_sbi_call(uint64_t which, uint64_t arg0, 
                uint64_t arg1, uint64_t arg2)
{
  register uint64_t a0 asm("a0") = arg0;
  register uint64_t a1 asm("a1") = arg1;
  register uint64_t a2 asm("a2") = arg2;
  register uint64_t a7 asm("a7") = which;
  asm volatile("ecall"
    : "+r"(a0)
    : "r" (a1), "r"(a2), "r"(a7)
    : "memory" 
  );
  return a0;
}