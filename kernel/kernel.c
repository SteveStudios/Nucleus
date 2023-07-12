// kernel.c - The main kernel manager
// Created 2023/7/10 by Stephen Byrne

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "atom_stdlib/io.h"
#include "data/utils.h"

#include "data/idt/idt.h"

#include "drivers/keyboardps2.h"

// First actions the kernel takes after starting up
void kernel_awake(void) {
    idt_init();
}

// Clear interrupts and halt
void kernel_hang(void) {
    asm ("cli");
    do {
        asm ("hlt");
    } while (true);
}

// Kernel update loop
void kernel_update(void) {
    while (__active)
    {
        if (get_key().m_key == (char*)'3')
            println("3 was pressed");
    }
}

// Entry point
void kernel_enter(void) {
    kernel_awake();
    kernel_update();
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) 
        kernel_hang();
}