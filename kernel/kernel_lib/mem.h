// mem.h - C standard library compliant memory function replacements
// Created 2023/7/10 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
# define MAP_ANONYMOUS MAP_ANON
#endif
#if !defined(MAP_FAILED)
# define MAP_FAILED ((char*)-1)
#endif

#ifndef MAP_NORESERVE
# ifdef MAP_AUTORESRV
#  define MAP_NORESERVE MAP_AUTORESRV
# else
#  define MAP_NORESERVE 0
# endif
#endif

#define PAGE_SIZE 4096
#define MAX_MEM 0x200000

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "memalloc.h"
#include "io.h"
#include "../headers/macros.h"
    
    extern bool is_locked;

    void *memcpy(void *dest, const void *src, size_t n);
    void *memset(void *s, int c, size_t n);
    void *memmove(void *dest, const void *src, size_t n);
    int memcmp(const void *s1, const void *s2, size_t n);

#ifdef __cplusplus
}
#endif