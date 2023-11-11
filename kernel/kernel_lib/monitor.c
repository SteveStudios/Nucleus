// monitor.c - Utilities for working with screens/monitors
// Created 2023/7/11 by Stephen Byrne

#include "monitor.h"

uint16_t get_bios_monitor(void)
{
    return *((uint16_t *)0x410);
}

// A monochrome monitor?
bool is_mono()
{
    return ((get_bios_monitor() & 0x30) == 0x30);
}

// A colour monitor?
bool is_col()
{
    return ((get_bios_monitor() & 0x30) == 0x20);
}

// No monitor, or an unknown one?
bool is_unknown()
{
    return ((get_bios_monitor() & 0x30) == 0x00);
}