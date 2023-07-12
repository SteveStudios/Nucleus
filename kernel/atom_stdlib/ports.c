// ports.c - In and out commands, which are useful for creating any device driver
// Created 2023/7/11 by Stephen Byrne

#include "ports.h"

// In command
unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile("in %%dx, %%al" : "=a"(ret) : "d"(port) : "memory");
    return ret;
}

// Out command
void outb(unsigned short port, unsigned char value)
{
    asm volatile("out %%al, %%dx" : : "a"(value), "d"(port) : "memory");
}