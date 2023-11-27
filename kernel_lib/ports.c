// ports.c - In and out commands, which are useful for creating any device driver
// Created 2023/7/11 by Stephen Byrne

#include "ports.h"

void outb(uint16_t port, uint8_t d)
{
    asm volatile(
        "outb %%al, %%dx"
        : : "d"(port), "a"(d));
}
unsigned char inb(uint16_t port)
{
    unsigned char val;
    asm volatile(
        "inb %%dx, %%al"
        : "=a"(val) : "d"(port));
    return val;
}

void outl(uint16_t port, uint32_t d)
{
    asm volatile("outl %0, %1"
                 : : "a"(d), "Nd"(port));
}

uint32_t inl(uint16_t port)
{
    uint32_t val;
    asm volatile("inl %1, %0"
                 : "=a"(val) : "Nd"(port));
    return val;
}

void io_wait()
{
    outb(0x80, 0);
}