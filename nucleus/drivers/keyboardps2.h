// keyboardps2.h - PS/2 keyboard implementation
// Created 2023/7/11 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "../nucleus_lib/ports.h"
#include "../nucleus_lib/io.h"

struct key_t
{
    char* m_key;
    uint8_t i_key;
    uint8_t last_key;
    bool key_pressed;
    bool released;
};

struct key_t get_key();
struct key_t key_from_uint8_t(uint8_t k, bool update_last_key);

#ifdef __cplusplus
}
#endif