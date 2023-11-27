// ports.h - In and out commands, which are useful for making pretty much every device driver
// Created 2023/7/11 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"

    void outb(uint16_t port, uint8_t d);
    unsigned char inb(uint16_t port);

    void outl(uint16_t port, uint32_t d);
    uint32_t inl(uint16_t port);

    void io_wait();

#ifdef __cplusplus
}
#endif
