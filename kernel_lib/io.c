// io.c - Terminal and input/output utilities
// Created 2023/7/11 by Stephen Byrne
#include "io.h"

static volatile struct limine_framebuffer_request framebuffer_request =
    {
        .id = LIMINE_FRAMEBUFFER_REQUEST,
        .revision = 0};

bool initialized = false;
struct flanterm_context *ft_ctx;

// Get the flanterm context; if it does not exist, initialize it
struct flanterm_context *get_ft_ctx()
{
    if (!initialized)
    {
        ft_ctx = flanterm_fb_simple_init((uint32_t *)framebuffer_request.response->framebuffers[0]->address,
                                         framebuffer_request.response->framebuffers[0]->width,
                                         framebuffer_request.response->framebuffers[0]->height,
                                         framebuffer_request.response->framebuffers[0]->pitch);
        initialized = true;
    }
    return ft_ctx;
}

// Clear the terminal by reinitializing the flanterm context
void clear_term()
{
    ft_ctx = flanterm_fb_simple_init((uint32_t *)framebuffer_request.response->framebuffers[0]->address,
                                     framebuffer_request.response->framebuffers[0]->width,
                                     framebuffer_request.response->framebuffers[0]->height,
                                     framebuffer_request.response->framebuffers[0]->pitch);
}


void number_to_character(int n)
{
    if (n == 0) {
        print("0");
        return;
    }

    int rev = 0, r = 0;
    while (n > 0)
    {
        r = n % 10;
        rev = rev * 10 + r;
        n = n / 10;
    }

    while (rev > 0)
    {
        r = rev % 10;

        switch (r)
        {
        case 1:
            print("1");
            break;
        case 2:
            print("2");
            break;
        case 3:
            print("3");
            break;
        case 4:
            print("4");
            break;
        case 5:
            print("5");
            break;
        case 6:
            print("6");
            break;
        case 7:
            print("7");
            break;
        case 8:
            print("8");
            break;
        case 9:
            print("9");
            break;
        case 0:
            print("0");
            break;
        }
        rev = rev / 10;
    }
}

// Write a string to video memory, printing a newline afterwards
void println(const char *str)
{
    flanterm_write(get_ft_ctx(), str, strlen(str));
    flanterm_write(get_ft_ctx(), "\n", strlen("\n"));
}

// Write a string to video memory
void print(const char *str)
{
    flanterm_write(get_ft_ctx(), str, strlen(str));
}

// Write a string to video memory, printing a newline afterwards
void println_int(int n)
{
    number_to_character(n);
    print("\n");
}

// Write a string to video memory
void print_int(int n)
{
    number_to_character(n);
}

// Prints a kernel panic warning
void kernel_panic()
{
    println("[ERROR] Kernel Panic");
}