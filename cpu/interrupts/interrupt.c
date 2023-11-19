// interrupt.c - Interrupt handler
// Created 2023/7/21 by Stephen Byrne

#include "interrupt.h"

// Called from (cpu/interrupts/asm/irq_helper.asm)
void handle_interrupt(int irq_n)
{
    if (inb(0x60) == 0xE0)
        last_key = 0xE0;

    switch (irq_n)
    {
    case 1:
        handle_keyboard();
        break;
    case 14:
        println("[INFO] Storage Device Ready");
        break;
    }

    if (irq_n >= 8)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

// Called from (cpu/interrupts/asm/irq_helper.asm)
void syscall(int rax, void* arg0, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5)
{
    switch (rax) {
        case 1:
            print((char*)arg1);
            break;   
    }
}