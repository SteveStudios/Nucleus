// macros.h - Global macro definitions
// Created 2023/11/10 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define AWAIT(condition)     \
    if (!condition)          \
    {                        \
        asm("cli");          \
        while (!condition)   \
        {                    \
        }                    \
        asm volatile("sti"); \
    }

#define KERNEL_LOC 0xffffffff80000000

#ifdef __cplusplus
}
#endif