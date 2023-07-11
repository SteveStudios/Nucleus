// monitor.h - Utilities for working with screens/monitors
// Created 2023/7/11 by Stephen Byrne

#include <stdbool.h>
#include <stdint.h>

inline uint16_t get_bios_monitor(void)
{
    return *((uint16_t*) 0x410);
}

// A monochrome monitor?
inline bool is_mono()
{
    return ((get_bios_monitor() & 0x30) == 0x30);
}

// A colour monitor?
inline bool is_col()
{
    return ((get_bios_monitor() & 0x30) == 0x20);
}

// No monitor, or a nonexistent one?
inline bool is_unknown()
{
    return ((get_bios_monitor() & 0x30) == 0x00);
}