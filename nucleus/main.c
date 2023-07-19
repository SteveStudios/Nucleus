// kernel.c - The main kernel manager
// Created 2023/7/10 by Stephen Byrne

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "stdlib/io.h"
#include "stdlib/utils.h"

#include "drivers/keyboardps2.h"

// First actions the kernel takes after starting up
void kernel_awake(void) {
    const char* logo = "  _   _            _\n| \\ | |_   _  ___| | ___ _   _ ___\n|  \\| | | | |/ __| |/ _ \\ | | / __|\n| |\\  | |_| | (__| |  __/ |_| \\__ \\\n|_| \\_|\\__,_|\\___|_|\\___|\\__,_|___/";
    println(logo);
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
        char* allowed_chars = "abcdefghijklmnopqrstuvwxyz1234567890|~#$%()*+-:;<=>@[]^_.,'!?";
    }
}

// Entry point
void kernel_enter(void) {
    kernel_awake();
    kernel_update();
    if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) 
        kernel_hang();
}