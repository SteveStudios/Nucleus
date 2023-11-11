// macros.h - Global macro definitions
// Created 2023/11/10 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define WAIT_UNTIL(condition) \
    if (!(condition))         \
    {                         \
        asm("cli");           \
        while (!condition)    \
        {                     \
        }                     \
        asm volatile("sti");  \
    }

#ifdef __cplusplus
}
#endif