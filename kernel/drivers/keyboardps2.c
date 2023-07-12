// keyboardps2.c - PS/2 keyboard implementation
// Created 2023/7/11 by Stephen Byrne

#include "keyboardps2.h"

// Translate key from 'uint8_t' to 'char'
struct key_t key_from_uint8_t(uint8_t k)
{
    char kc;
    struct key_t k_s;

    switch (k)
    {
        case 0x04:
            kc = '3';
            k_s.released = false;
            break;
    
        default:
            break;
    }
    k_s.m_key = kc;
    return k_s;
}

// Get the current pressed key, returns a null character if nothing was found
struct key_t get_key()
{
    uint8_t k = 0;
    if(inb(0x64) & 1)
    {
		k = inb(0x60);
        return key_from_uint8_t(k);
    }

    struct key_t k_s;
    k_s.m_key = '\0';

    return k_s;
}