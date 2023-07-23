// idt.c - Interrupt and IDT (Interrupt Descriptor Table) handler
// Created 2023/7/20 by Stephen Byrne

#include "idt.h"

// An instance of the IDT
typedef struct
{
	uint16_t isr_low;
	uint16_t kernel_cs;
	uint8_t ist;
	uint8_t attributes;
	uint16_t isr_mid;
	uint32_t isr_high;
	uint32_t reserved;
} __attribute__((__packed__)) idt_instance_t;

// IDT register interface
typedef struct
{
	uint16_t limit;
	uint64_t base;
} __attribute__((__packed__)) idtr_t;

// IDT Buffer
idt_instance_t idt[256];

// See "main.c"
extern void kernel_hang();

// Translates "e_code" to a string describing the exception that occured.
char *e_code_to_str(uint8_t e_code)
{
	switch (e_code)
	{
	case 0:
		return (char *)"Division by zero";
	case 1:
		return (char *)"Debug Error";
	case 2:
		return (char *)"Non Maskable Interrupt";
	case 3:
		return (char *)"Int 3 Error";
	case 4:
		return (char *)"INTO Error";
	case 5:
		return (char *)"Out of Bounds";
	case 6:
		return (char *)"Invalid opcode";
	case 7:
		return (char *)"Coprocessor not available";
	case 8:
		return (char *)"Double Fault";
	case 9:
		return (char *)"Coprocessor Segment Overrun";
	case 10:
		return (char *)"Bad TSS";
	case 11:
		return (char *)"Segment not Present";
	case 12:
		return (char *)"Stack Fault";
	case 13:
		return (char *)"General Protection Fault";
	case 14:
		return (char *)"Page Fault";
	case 16:
		return (char *)"Floating Point Error";
	case 17:
		return (char *)"Alignment Check Error";
	case 18:
		return (char *)"Machine Check Error";
	case 19:
	default:
		return (char *)"Reserved";
	}
	return (char *)"\0";
}

// Exception handler (Called from cpu/interrupts/asm/idt_exception.s)
// "e_code" describes the ISR handler where said exception occured.
void on_exception(uint8_t e_code)
{
	kernel_panic();

	print("EXCEPTION: ");
	print(e_code_to_str(e_code));

	kernel_hang();
}

// Set an IDT descriptor
void idt_set_descriptor(uint8_t vector, void *isr)
{
	idt_instance_t *descriptor = &idt[vector];
	descriptor->isr_low = (uint64_t)isr & 0xFFFF;
	descriptor->kernel_cs = 0x28;
	descriptor->ist = 0;
	descriptor->attributes = 0x8E;
	descriptor->isr_mid = ((uint64_t)isr >> 16) & 0xFFFF;
	descriptor->isr_high = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
	descriptor->reserved = 0;
}

// Enable non-maskable interrupts
void nm_interrupt_enable()
{
	outb(0x70, inb(0x70) & 0x7F);
	inb(0x71);
}

// Disable non-maskable interrupts
void nm_interrupt_disable()
{
	outb(0x70, inb(0x70) | 0x80);
	inb(0x71);
}

// Remap PIC function and defines
// SEE: https://wiki.osdev.org/8259_PIC#Initialisation

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08	
#define ICW1_INIT 0x10

#define ICW4_8086 0x01	
#define ICW4_AUTO 0x02*/
#define ICW4_BUF_SLAVE 0x08 
#define ICW4_BUF_MASTER 0x08
#define ICW4_SFNM 0x10

void remap_pic(int offset1, int offset2)
{
	unsigned char a1, a2;

	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, offset1); 
	io_wait();
	outb(PIC2_DATA, offset2); 
	io_wait();
	outb(PIC1_DATA, 4);
	io_wait();
	outb(PIC2_DATA, 2); 
	io_wait();

	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);
}

// Initialize the IDT
void idt_init()
{
	// Setup ISRs
	idt_set_descriptor(0, isr0);
	idt_set_descriptor(1, isr1);
	idt_set_descriptor(2, isr2);
	idt_set_descriptor(3, isr3);
	idt_set_descriptor(4, isr4);
	idt_set_descriptor(5, isr5);
	idt_set_descriptor(6, isr6);
	idt_set_descriptor(7, isr7);
	idt_set_descriptor(8, isr8);
	idt_set_descriptor(9, isr9);
	idt_set_descriptor(10, isr10);
	idt_set_descriptor(11, isr11);
	idt_set_descriptor(12, isr12);
	idt_set_descriptor(13, isr13);
	idt_set_descriptor(14, isr14);
	idt_set_descriptor(15, isr15);
	idt_set_descriptor(16, isr16);
	idt_set_descriptor(17, isr17);
	idt_set_descriptor(18, isr18);
	idt_set_descriptor(19, isr19);
	idt_set_descriptor(20, isr20);
	idt_set_descriptor(21, isr21);
	idt_set_descriptor(22, isr22);
	idt_set_descriptor(23, isr23);
	idt_set_descriptor(24, isr24);
	idt_set_descriptor(25, isr25);
	idt_set_descriptor(26, isr26);
	idt_set_descriptor(27, isr27);
	idt_set_descriptor(28, isr28);
	idt_set_descriptor(29, isr29);
	idt_set_descriptor(30, isr30);
	idt_set_descriptor(31, isr31);

	// Remap PIC
	remap_pic(0x20, 0x28);

	// Enable keyboard interrupts
	outb(0x21, 0xFD);
	outb(0xA1, 0xFF);

	// Setup IRQs
	idt_set_descriptor(32, irq0);
	idt_set_descriptor(33, irq1);
	idt_set_descriptor(34, irq2);
	idt_set_descriptor(35, irq3);
	idt_set_descriptor(36, irq4);
	idt_set_descriptor(37, irq5);
	idt_set_descriptor(38, irq6);
	idt_set_descriptor(39, irq7);
	idt_set_descriptor(40, irq8);
	idt_set_descriptor(41, irq9);
	idt_set_descriptor(42, irq10);
	idt_set_descriptor(43, irq11);
	idt_set_descriptor(44, irq12);
	idt_set_descriptor(45, irq13);
	idt_set_descriptor(46, irq14);
	idt_set_descriptor(47, irq15);

	// Enable non-maskable interrupts
	nm_interrupt_enable();

	// IDT register accessor
	idtr_t idtr = {(sizeof(idt_instance_t) * 256) - 1, (uint64_t)&idt};

	// Load the IDT register
	asm volatile("lidt %0"
				 :
				 : "m"(idtr));

	enable_apic();
}