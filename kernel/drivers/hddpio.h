// hdd_pio.h - HDD PIO Driver
// Created 2023/7/10 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "../kernel_lib/ports.h"

void read_sector(int, unsigned char);

#ifdef __cplusplus
}
#endif