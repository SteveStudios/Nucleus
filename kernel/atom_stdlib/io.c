// io.c - Terminal and input/output utilituies
// Created 2023/7/11 by Stephen Byrne
#include "str.h"

#include "io.h"

static volatile struct limine_framebuffer_request framebuffer_request = 
{
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Write a string to video memory, default color is white
void println(const char* str) {
    struct flanterm_context *ft_ctx = flanterm_fb_simple_init((uint32_t*)framebuffer_request.response->framebuffers[0]->address, 
                                                            framebuffer_request.response->framebuffers[0]->width, 
                                                            framebuffer_request.response->framebuffers[0]->height, 
                                                            framebuffer_request.response->framebuffers[0]->pitch);
    flanterm_write(ft_ctx, str, strlen(str));
    flanterm_write(ft_ctx, "\n", 2);
}

void print(const char* str) {
    struct flanterm_context *ft_ctx = flanterm_fb_simple_init((uint32_t*)framebuffer_request.response->framebuffers[0]->address, 
                                                            framebuffer_request.response->framebuffers[0]->width, 
                                                            framebuffer_request.response->framebuffers[0]->height, 
                                                            framebuffer_request.response->framebuffers[0]->pitch);
    flanterm_write(ft_ctx, str, strlen(str));
}