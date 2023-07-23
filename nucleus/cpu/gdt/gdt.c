// gdt.c - GDT (Global Descriptor Table) manager
// Created 2023/7/20 by Stephen Byrne

#include "gdt.h"

uint64_t gdt[] = 
{
    0x0000000000000000, 
    0x00009a000000ffff,
    0x000093000000ffff,
    0x00cf9a000000ffff, 
    0x00cf93000000ffff, 
    0x00af9b000000ffff, 
    0x00af93000000ffff, 
    0x00affb000000ffff, 
    0x00aff3000000ffff
};

// Initialize the GDT
void gdt_init()
{   
    asm("cli");

    gdtr_t gdtr = {sizeof(gdt) - 1, (uint64_t)&gdt};
    asm volatile("lgdt %0" : : "m"(gdtr));

    reload_segment_registers();
}
