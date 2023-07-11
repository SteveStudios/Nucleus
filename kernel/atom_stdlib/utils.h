// utils.h - Variables and minimal functions that are used pretty much everywhere, or just play an important role in the kernel
// Created 2023/7/10 by Stephen Byrne
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t global_dt[] =
{
    0x0000000000000000,
    0x00009a000000ffff,
    0x000093000000ffff,
    0x00cf9a000000ffff,
    0x00cf93000000ffff,
    0x00af9b000000ffff,
    0x00af93000000ffff,
    0x00affb000000ffff,
    0x00aff3000000ffff
};

bool __active = false;

#ifdef __cplusplus
}
#endif