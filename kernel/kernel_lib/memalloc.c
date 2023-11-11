// alloc.c - Advanced memory allocation utilities
// Created 2023/11/10 by Stephen Byrne

#include "memalloc.h"

int total_pages;
int free_pages;
int last_page;

int mem_buf[((MAX_MEM / 4) / 8) + 1];

#define MARK_USED(block)                                     \
    mem_buf[((block) / 8)] |= (uint8_t)(1 << ((block) % 8)); \
    free_pages--

#define FREE(block)                                             \
    mem_buf[((block) / 8)] &= ~((uint8_t)(1 << ((block) % 8))); \
    free_pages++

#define IN_USE(block) \
    (mem_buf[((block) / 8)] & (uint8_t)(1 << ((block) % 8))) != 0

void *alloc_page(int pages)
{
    int block = -1;
    for (int i = 0; i < total_pages; i++)
    {
        int pos = (i + last_page) % total_pages;
        if ((pos + pages) > total_pages)
        {
            i += pages - 2;
            continue;
        }

        block = pos;
        for (int j = 0; j < pages; j++)
        {
            if (IN_USE(pos + j))
            {
                block = -1;
                i = i + j;
                break;
            }
        }
        if (block != -1)
            break;
    }

    if (block == -1)
    {
        if (is_locked)
            asm volatile("sti");
        return NULL;
    }

    for (int k = 0; k < pages; k++)
    {
        MARK_USED(block + k);
    }

    last_page = block + pages;
    if (is_locked)
        asm volatile("sti");
    return (void *)((unsigned int)block * PAGE_SIZE);
}

void free_page(void *position, int pages)
{
    int start, index;

    start = ((uint32_t)position) / PAGE_SIZE;

    for (index = 0; index < pages; index++)
    {
        int block = start + index;
        FREE(block);
    }

    if (!is_locked)
        asm volatile("sti");
}

void init_mem()
{
    for (int i = 0; i < ((MAX_MEM / 4) / 8) + 1; i++)
    {
        mem_buf[i] = 0xFF;
    }

    total_pages = MAX_MEM / 4;
    free_pages = 0;
    last_page = 0;
}