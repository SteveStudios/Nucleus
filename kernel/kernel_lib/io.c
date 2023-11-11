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

// Write a string to video memory, printing a newline afterwards, default color is white
void println(const char *str)
{
    flanterm_write(get_ft_ctx(), str, strlen(str));
    flanterm_write(get_ft_ctx(), "\n", strlen("\n"));
}

// Write a string to video memory, default color is white
void print(const char *str)
{
    flanterm_write(get_ft_ctx(), str, strlen(str));
}

// Prints a kernel panic warning
void kernel_panic()
{
    println("!!KERNEL PANIC!!");
}