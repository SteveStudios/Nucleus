// apic.c - APIC driver
// Created 2023/7/11 by Stephen Byrne

#include "apic.h"

// Useful macros
#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100 
#define IA32_APIC_BASE_MSR_ENABLE 0x800
 
// Set the APIC base
void cpu_set_apic_base(uintptr_t apic) {
   uint32_t edx = 0;
   uint32_t eax = (apic & 0xfffff0000) | IA32_APIC_BASE_MSR_ENABLE;
 
#ifdef __PHYSICAL_MEMORY_EXTENSION__
   edx = (apic >> 32) & 0x0f;
#endif
 
   cpuSetMSR(IA32_APIC_BASE_MSR, eax, edx);
}
 
// Get the APIC base
uintptr_t cpu_get_apic_base() {
   uint32_t eax, edx;
   cpuGetMSR(IA32_APIC_BASE_MSR, &eax, &edx);
 
#ifdef __PHYSICAL_MEMORY_EXTENSION__
   return (eax & 0xfffff000) | ((edx & 0x0f) << 32);
#else
   return (eax & 0xfffff000);
#endif
}

// Initialize the APIC
void apic_init() {
    cpu_set_apic_base(cpu_get_apic_base());
    write_reg(0xF0, ReadRegister(0xF0) | 0x100);
}