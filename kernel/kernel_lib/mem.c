// mem.c - C standard library compliant memory function replacements
// Created 2023/7/10 by Stephen Byrne

#include "mem.h"

bool is_locked = false;

void *memcpy(void *dest, const void *src, size_t n)
{
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    for (size_t i = 0; i < n; i++)
    {
        pdest[i] = psrc[i];
    }
    return dest;
}

void *memset(void *s, int c, size_t n)
{
    uint8_t *p = (uint8_t *)s;

    for (size_t i = 0; i < n; i++)
    {
        p[i] = (uint8_t)c;
    }

    return s;
}

void *memmove(void *dest, const void *src, size_t n)
{
    uint8_t *pdest = (uint8_t *)dest;
    const uint8_t *psrc = (const uint8_t *)src;

    if (src > dest)
    {
        for (size_t i = 0; i < n; i++)
        {
            pdest[i] = psrc[i];
        }
    }
    else if (src < dest)
    {
        for (size_t i = n; i > 0; i--)
        {
            pdest[i - 1] = psrc[i - 1];
        }
    }
    return dest;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const uint8_t *p1 = (const uint8_t *)s1;
    const uint8_t *p2 = (const uint8_t *)s2;

    for (size_t i = 0; i < n; i++)
    {
        if (p1[i] != p2[i])
        {
            return p1[i] < p2[i] ? -1 : 1;
        }
    }
    return 0;
}

int liballoc_lock()
{
    if (!is_locked)
    {
        asm("cli");
        is_locked = !is_locked;
    }
    return is_locked;
}

int liballoc_unlock()
{
    if (is_locked)
    {
        asm volatile("sti");
        is_locked = !is_locked;
    }
    return is_locked;
}

void *liballoc_alloc(int pages)
{
    void *ptr_ret = NULL;
    asm ("cli");

    WAIT_UNTIL(pages > 0);
    
    if (free_pages < pages)
	{
		asm ("sti");
		return NULL;
	}

    ptr_ret = alloc_page(pages);
    if (ptr_ret == NULL) println("[ERROR] Out of memory");

    asm ("sti");
    return ptr_ret;
}

int liballoc_free(void *ptr, int pages)
{
    free_page(ptr, pages);
    return 0;
}