// kernel.c - Contains kernel entry point
// Created 2023/7/10 by Stephen Byrne

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "atom_stdlib/io.h"
#include "atom_stdlib/utils.h"

// First actions the kernel takes after starting up
void kernel_awake(void) {
    println("Hello, world!");
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
        if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) 
            kernel_hang();
    }
}

// Entry point
void kernel_enter(void) {
    kernel_awake();
    kernel_update();
}