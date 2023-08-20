// main.c - The main kernel manager
// Created 2023/7/10 by Stephen Byrne

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "kernel_lib/io.h"

#include "drivers/keyboardps2.h"

#include "handlers/handler_keyboardps2.h"

#include "cpu/interrupts/idt.h"
#include "cpu/gdt/gdt.h"

void print_logo()
{
    const char *logo = "     _   _                   ___  ____\n    / \\ | |_ ___  _ __ ___  / _ \\/ ___|\n   / _ \\| __/ _ \\| '_ ` _ \\| | | \\___ \\\n  / ___ \\ || (_) | | | | | | |_| |___) |\n /_/   \\_\\__\\___/|_| |_| |_|\\___/|____/";
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

// Entry point
void kernel_enter(void)
{   
    kernel_awake();

    // Enable interrupts
	asm volatile("sti");

    // Make sure the system doesn't exit for no reason
    for (;;)
        asm ("hlt");
}