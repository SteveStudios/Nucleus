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

    struct mem_req
    {
        uint64_t phys_addr, dest_addr;
        size_t len;
    };

    struct mem_res
    {
        size_t len;
        void *buf;
    };

#ifdef __cplusplus
}
#endif