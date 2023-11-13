// mem.h - C standard library compliant memory function replacements
// Created 2023/7/10 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define PAGE_SIZE 4096
#define MAX_MEM 0x200000

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "memalloc.h"
#include "io.h"
#include "../include/macros.h"
    
    extern bool is_locked;

    void *memcpy(void *dest, const void *src, size_t n);
    void *memset(void *s, int c, size_t n);
    void *memmove(void *dest, const void *src, size_t n);
    int memcmp(const void *s1, const void *s2, size_t n);

#ifdef __cplusplus
}
#endif