// interrupt.c - Interrupt handler
// Created 2023/7/21 by Stephen Byrne

#include "interrupt.h"

// Called from (cpu/interrupts/asm/irq_helper.asm)
void handle_interrupt(uint8_t irq_n)
{   if (inb(0x60) == 0xE0)
        last_key = 0xE0;
    handle_keyboard();

    if (irq_n >= 8)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);
}