// alloc.c - Advanced memory allocation utilities
// Created 2023/11/10 by Stephen Byrne

#include "memalloc.h"

int mem_buf[((MAX_MEM / 4) / 8) + 1];

void alloc_single_page()
{
    for (int i = 0; i < ((MAX_MEM / 4) / 8) + 1; i++)
    {
        if (mem_buf[i] == 0x00)
        {
            mem_buf[i] = 0x01;
            break;
        }
    }
}

void *alloc_page(int pages)
{
    uint32_t ret;
    uint32_t i;

    for (i = 0; i < pages; i++)
    {
        alloc_single_page();
    }
    return (void *)((unsigned int)i * PAGE_SIZE);
}

void free_page(void *position, int pages)
{
    for (int i = (int)position / PAGE_SIZE; i < pages; i++)
    {
        mem_buf[i] = 0x00;
    }
}

void init_mem()
{
    for (int i = 0; i < ((MAX_MEM / 4) / 8) + 1; i++)
    {
        mem_buf[i] = 0x00;
    }
}