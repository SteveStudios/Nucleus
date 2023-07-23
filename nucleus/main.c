// kernel.c - The main kernel manager
// Created 2023/7/10 by Stephen Byrne

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "nucleus_lib/io.h"

#include "drivers/keyboardps2.h"

#include "handlers/handler_keyboardps2.h"

#include "opt/defines.h"

#include "cpu/interrupts/idt.h"
#include "cpu/gdt/gdt.h"

void print_logo()
{
    const char *logo = " _   _            _\n| \\ | |_   _  ___| | ___ _   _ ___\n|  \\| | | | |/ __| |/ _ \\ | | / __|\n| |\\  | |_| | (__| |  __/ |_| \\__ \\\n|_| \\_|\\__,_|\\___|_|\\___|\\__,_|___/";
    println("________________________________________________________");
    println(logo);
    println("________________________________________________________");
}

// First actions the kernel takes after starting up
void kernel_awake(void)
{
    gdt_init();
    idt_init();

    print_logo();
}

// Clear interrupts and halt
void kernel_hang(void)
{
    for (;;)
        asm ("cli; hlt");
}

#ifdef POLLING
// Kernel update loop (Is only called if POLLING is set to true)
void kernel_update(void)
{
    while (true)
    {
        handle_keyboard();
    }
}
#endif

// Entry point
void kernel_enter(void)
{   
    kernel_awake();
    
    #ifdef POLLING
    kernel_update();
    #else
    for (;;)
        asm ("hlt");
    #endif
}