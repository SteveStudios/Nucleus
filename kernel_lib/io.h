// io.h - Terminal and input/output utilituies
// Created 2023/7/11 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>

#include "../lib/limine/limine.h"

#include "../lib/flanterm/flanterm.h"
#include "../lib/flanterm/backends/fb.h"

#include "str.h"

    static volatile struct limine_framebuffer_request framebuffer_request;

    void println(const char *str);
    void print(const char *str);

    void println_int(int n);
    void print_int(int n);

    void clear_term();

    void kernel_panic();

#ifdef __cplusplus
}
#endif