// alloc.h - Advanced memory allocation utilities
// Created 2023/11/10 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "mem.h"

    extern int total_pages;
    extern int free_pages;
    extern int last_page;

    void init_mem(void);
    void *alloc_page(int);
    void free_page(void*, int);

#ifdef __cplusplus
}
#endif