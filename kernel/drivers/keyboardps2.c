// keyboardps2.c - PS/2 keyboard implementation
// Created 2023/7/11 by Stephen Byrne

#include "keyboardps2.h"

#include "../atom_stdlib/ports.h"

// Translate key from 'uint8_t' to 'char'
char key_from_uint8_t(uint8_t k)
{
    char kc;
    switch (k)
    {
        case 0x04:
            kc = '3';
            break;
    
        default:
            break;
    }
    return kc;
}

// Get the current pressed key, returns a null character if nothing was found
char get_key()
{
    uint8_t k = 0;
    if(inb(0x64) & 1)
    {
		k = inb(0x60);
        return key_from_uint8_t(k);
    }
    return '\0';
}