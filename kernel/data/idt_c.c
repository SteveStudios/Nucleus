// idt_c.c - Interrupt descriptor table and ISR utilities
// Created 2023/7/11 by Stephen Byrne

// REFERENCES USED: https://dev.to/frosnerd/writing-my-own-keyboard-driver-16kh

#include "idt.h"

#define __low(addr) (uint16_t)((addr) & 0xFFFF)
#define __high(addr) (uint16_t)(((addr) >> 16) & 0xFFFF)

// Possible IDT gates
typedef volatile struct {
    uint16_t low_offset;
    uint16_t m_selector;
    uint8_t always_zero;
    uint8_t m_flags;
    uint16_t high_offset;
}  idt_gates;

// IDT Buffer
idt_gates idt[256];

// Set an IDT gate to 'val'
void idt_setgate(int gate, uint32_t val)
{
    idt[gate].low_offset = __low(val);
    idt[gate].high_offset = __high(val);

    idt[gate].always_zero = 0;

    idt[gate].m_flags = 0x8E;
    idt[gate].m_selector = 0x08;
}

// Possible error messages
const char* errors[] = {"Division By Zero", "Debug Error", "Stack Fault", "Reserved"};

// Assembly registers
typedef struct {
    uint32_t ds, edi, esi, ebp, esp, ebx, edx, ecx, eax, int_no, err_code, eip, cs, eflags, useresp, ss;
} asm_register;

// Prints said exception message (But does not catch it)
void print_e(asm_register *r) {
    println(errors[r->int_no]);
}

extern int isr0;
extern int isr1;
extern int isr31;

// Initialize the IDT
void idt_init()
{
    idt_setgate(0, (uint32_t)isr0);
    idt_setgate(1, (uint32_t)isr1);
    idt_setgate(31, (uint32_t)isr31);
}