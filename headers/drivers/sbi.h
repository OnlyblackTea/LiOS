#ifndef __SBI_H__
#define __SBI_H__

#include <stdint.h>

uint64_t k_sbi_call(uint64_t,uint64_t,uint64_t,uint64_t);
void ecall_putchar(unsigned long c);
unsigned long ecall_getchar();
void ecall_shutdown();

#endif