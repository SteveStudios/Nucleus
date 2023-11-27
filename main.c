// main.c - File containing the kernel entry point
// Created 2023/7/10 by Stephen Byrne

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "kernel_lib/io.h"

#include "drivers/keyboardps2.h"
#include "drivers/pci.h"
#include "drivers/ext4.h"

#include "handlers/handler_keyboardps2.h"

#include "cpu/interrupts/idt.h"
#include "cpu/gdt/gdt.h"

#include "kernel_lib/memalloc.h"

// First actions the kernel takes after starting up
void kernel_awake()
{   
    println("[INFO] Initializing Allocator...");
    init_mem();
    println("[INFO] Initialized Allocator");
    
    println("[INFO] Initializing GDT...");
    gdt_init();
    println("[INFO] Initialized GDT");

    println("[INFO] Initializing IDT...");
    idt_init();
    println("[INFO] Initialized IDT");
}

// Disable interrupts and halt
void kernel_hang()
{
    for (;;)
        asm("cli; hlt");
}

bool error = false;
extern uint32_t devs;

// Entry point
void kernel_enter(void)
{
    kernel_awake();

    println("[INFO] Initializing PCI Driver...");
    pci_init();
    println("[INFO] Initialized PCI Driver");

    println("[EXT4] Initializing Filesystem...");
    if (init_ext4(8))  {
        error = true;
        println("[EXT4] Failed to initialize Filesystem");
    }
    else println("[EXT4] Initialized Filesystem");

    println("[INFO] Enabling Interrupts...");
    
    // Enable interrupts
    asm volatile("sti");
    
    println("[INFO] Enabled Interrupts");

    if (error)
        println("[WARNING] Nucleus booted with errors");
    else println("[INFO] Nucleus booted successfully");

    // Make sure the system doesn't exit for no reason
    for (;;)
        asm("hlt");
}