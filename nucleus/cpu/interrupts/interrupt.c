// interrupt.c - Interrupt handler
// Created 2023/7/21 by Stephen Byrne

#include "interrupt.h"

// Called from (cpu/interrupts/asm/irq_helper.asm)
void handle_interrupt(uint8_t irq_n)
{   
    handle_keyboard();

    if (irq_n >= 8)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);
}