// ports.h - In and out commands, which are useful for making pretty much every device driver
// Created 2023/7/11 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    unsigned char inb(unsigned short port);
    void outb(unsigned short port, unsigned char value);

    void io_wait();

#ifdef __cplusplus
}
#endif
