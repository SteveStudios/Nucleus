// keyboardps2.h - PS/2 keyboard implementation
// Created 2023/7/11 by Stephen Byrne

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "../atom_stdlib/ports.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct key_t
{
    char m_key;
    bool released;
};

struct key_t get_key();


#ifdef __cplusplus
}
#endif