// io.h - Terminal and input/output utilituies
// Created 2023/7/11 by Stephen Byrne

#pragma once

#include "../../lib/limine/limine.h"

#include "../../lib/flanterm/flanterm.h"
#include "../../lib/flanterm/backends/fb.h"

#include "str.h"

static volatile struct limine_framebuffer_request framebuffer_request = 
{
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

// Write a string to video memory, default color is white
static void println(const char* str) {
    struct flanterm_context *ft_ctx = flanterm_fb_simple_init(framebuffer_request.response->framebuffers[0]->address, 
                                                            framebuffer_request.response->framebuffers[0]->width, 
                                                            framebuffer_request.response->framebuffers[0]->height, 
                                                            framebuffer_request.response->framebuffers[0]->pitch);
    flanterm_write(ft_ctx, str, strlen(str));
}