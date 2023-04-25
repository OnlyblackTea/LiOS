#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

#define UART        0x10000000
#define UART_THR    (uint8_t*)(UART+0x00)
#define UART_LSR    (uint8_t*)(UART+0x05)
#define UART_LSR_EMPTY_MASK 0x40

#endif