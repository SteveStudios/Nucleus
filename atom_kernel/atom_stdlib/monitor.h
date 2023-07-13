// monitor.h - Utilities for working with screens/monitors
// Created 2023/7/11 by Stephen Byrne
#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint16_t get_bios_monitor(void);

bool is_mono();
bool is_col();
bool is_unknown();

#ifdef __cplusplus
}
#endif