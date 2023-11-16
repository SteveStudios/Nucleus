// apic.c - APIC setup helper
// Created 2023/7/21 by Stephen Byrne

#include "apic.h"

void cpuid(int code, uint32_t *a, uint32_t *d)
{
    asm volatile("cpuid"
                 : "=a"(*a), "=d"(*d)
                 : "a"(code)
                 : "ecx", "ebx");
}

bool check_apic()
{
    uint32_t eax, edx;
    cpuid(1, &eax, &edx);
    return edx & 0x100;
}

void get_msr(uint32_t msr, uint32_t *lo, uint32_t *hi)
{
    asm volatile("rdmsr"
                 : "=a"(*lo), "=d"(*hi)
                 : "c"(msr));
}

void set_msr(uint32_t msr, uint32_t lo, uint32_t hi)
{
    asm volatile("wrmsr"
                 :
                 : "a"(lo), "d"(hi), "c"(msr));
}

void set_base(uintptr_t apic)
{
    uint32_t edx = 0;
    uint32_t eax = (apic & 0xfffff0000) | 0x800;

    set_msr(0x1B, eax, edx);
}

uintptr_t get_base()
{
    uint32_t eax, edx;
    get_msr(0x1B, &eax, &edx);

    return (eax & 0xfffff000);
}

uint32_t read_register(uint32_t reg)
{
    return *((volatile uint32_t *)(get_base() + reg));
}

void write_register(uint32_t reg, uint32_t value)
{
    *((volatile uint32_t *)(get_base() + reg)) = value;
}

void enable_apic()
{
    set_base(get_base());
    write_register(0xF0, read_register(0xF0) | 0x100);
}