/**
 * @file ports.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef KERNEL_CPU_H
#define KERNEL_CPU_H

#include <types.h>

extern uint8_t inb(uint16_t port);
extern void outb(uint16_t port, uint8_t data);
extern uint16_t inw(uint16_t port);
extern void outw(uint16_t port, uint16_t data);
extern uint8_t in8(uint16_t port);
extern void out8(uint16_t port, uint8_t data);
extern uint16_t in16(uint16_t port);
extern void out16(uint16_t port, uint16_t data);
uint32_t in32(uint16_t port);
void out32(uint16_t port, uint32_t data);

#define outb_p(port, value) \
__asm__("outb %%al, %%dx\n" \
        "\tjmp 1f\n"        \
        "1:\tjmp 1f\n"      \
        "1:"::"a" (value), "d" (port))

#define inb_p(port) ({                  \
uint8_t __res;                          \
__asm__ volatile ("inb %%dx, %%al\n"    \
    "\tjmp 1f\n"                        \
    "1:\tjmp 1f\n"                      \
    "1:":"=a" (__res):"d" (port));      \
__res;                                  \
})

#endif
