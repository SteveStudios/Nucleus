// keyboardps2.c - PS/2 keyboard implementation
// Created 2023/7/11 by Stephen Byrne

#include "keyboardps2.h"

// Translate key from 'uint8_t' to 'char'
struct key_t key_from_uint8_t(uint8_t k)
{
    char* kc;
    struct key_t k_s;
    
    switch (k)
    {
        case 0x04:
            kc = (char*)'3';
            k_s.released = false;
            break;

        case 0x08:
            kc = (char*)'7';
            k_s.released = false;
            break;
    
        case 0x0C:
            kc = (char*)'-';
            k_s.released = false;
            break;
        
        case 0x10:
            kc = (char*)'q';
            k_s.released = false;
            break;

        case 0x14:
            kc = (char*)'t';
            k_s.released = false;
            break;

        case 0x18:
            kc = (char*)'o';
            k_s.released = false;
            break;
        
        case 0x1C:
            kc = (char*)"enter";
            k_s.released = false;
            break;

        case 0x20:
            kc = (char*)'d';
            k_s.released = false;
            break;

        case 0x24:
            kc = (char*)'j';
            k_s.released = false;
            break;

        case 0x28:
            kc = (char*)'\'';
            k_s.released = false;
            break;
        
        case 0x2C:
            kc = (char*)'z';
            k_s.released = false;
            break;

        case 0x30:
            kc = (char*)'b';
            k_s.released = false;
            break;

        case 0x34:
            kc = (char*)'.';
            k_s.released = false;
            break;
            
        case 0x38:
            kc = (char*)"lalt";
            k_s.released = false;
            break;

        case 0x3C:
            kc = (char*)"f2";
            k_s.released = false;
            break;

        case 0x40:
            kc = (char*)"f6";
            k_s.released = false;
            break;

        case 0x44:
            kc = (char*)"f10";
            k_s.released = false;
            break;

        case 0x48:
            kc = (char*)"kp_8";
            k_s.released = false;
            break;

        case 0x4C:
            kc = (char*)"kp_5";
            k_s.released = false;
            break;

        case 0x50:
            kc = (char*)"kp_2";
            k_s.released = false;
            break;  

        case 0x57:
            kc = (char*)"f11";
            k_s.released = false;
            break;   

        case 0x58:
            kc = (char*)"f12";
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
    // Key scancode
    uint8_t k = 0;
    
    if (inb(0x64) & 1)
    {
		k = inb(0x60);
        return key_from_uint8_t(k);
    }

    struct key_t k_s;
    k_s.m_key = '\0';

    return k_s;
}