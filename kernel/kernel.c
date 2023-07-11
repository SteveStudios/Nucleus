// kernel.c - Contains kernel entry point
// Created 2023/7/10 by Stephen Byrne

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "atom_stdlib/io.h"
#include "../limine/limine.h"
 
static volatile struct limine_framebuffer_request framebuffer_request = 
{
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// First actions the kernel takes after starting up
void kernel_awake(void) {
    println("Hello, world!", WHITE);
}

// Clear interrupts and halt
static void kernel_hang(void) {
    asm ("cli");
    do {
        asm ("hlt");
    } while (true);
}

// Entry point
void kernel_enter(void) {
    kernel_awake();
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) 
        kernel_hang();
    kernel_hang();
}