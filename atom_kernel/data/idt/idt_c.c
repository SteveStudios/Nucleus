// idt_c.c - Interrupt descriptor table, IRQ, and ISR utilities
// Created 2023/7/11 by Stephen Byrne

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
void print_e(asm_register *m_register) {
    println(errors[m_register->int_no]);
}

// ISR assembly externs
extern int isr0;
extern int isr1;
extern int isr31;

// ISR Type
typedef void (*isr_t)(asm_register*);

// IDT registers
typedef volatile struct 
{
    uint32_t base;
    uint16_t limit;
} idt_register;

// ISR Buffer
isr_t i_h[256];

// IRQ assembly externs
extern int irq0;
extern int irq7;
extern int irq8;
extern int irq15;

// Handle an interrupt request
void irq_handler(asm_register *m_register) {
    if (i_h[m_register->int_no] != 0) 
    {
        isr_t handler = i_h[m_register->int_no];
        handler(m_register);
    }

    outb(0x20, 0x20);
    if (m_register->int_no < 40)
        outb(0xA0, 0x20);
}

// The said IDT regiser
idt_register r;

// Load the IDT
void load_idt() {
    r.base = *(uint64_t*)&idt;
    r.limit = 256 * sizeof(idt_gates) - 1;
    asm volatile("lidt (%0)" : : "r" (&r));
}

// Initialize the IDT
void idt_init()
{
    // Set up ISRs
    idt_setgate(0, (uint32_t)isr0);
    idt_setgate(1, (uint32_t)isr1);
    idt_setgate(31, (uint32_t)isr31);

    // Set up ICWs and OCWs
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    // Set up primary IRQs
    idt_setgate(32, (uint32_t)irq0);
    idt_setgate(39, (uint32_t)irq7);

    // Set up secondary IRQs
    idt_setgate(40, (uint32_t)irq8);
    idt_setgate(47, (uint32_t)irq15);

    // Load the IDT
    load_idt();
}