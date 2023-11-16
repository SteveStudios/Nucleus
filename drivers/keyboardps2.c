// keyboardps2.c - PS/2 keyboard implementation
// Created 2023/7/11 by Stephen Byrne

#include "keyboardps2.h"

uint8_t last_key = 0;

// Translate key from "uint8_t" to "char"
struct key_t key_from_uint8_t(uint8_t k, bool update_last_key)
{
    char *kc = "\0";
    struct key_t k_s;

    k_s.i_key = k;
    if (update_last_key)
        k_s.last_key = last_key;

    switch (k)
    {
    case 0x04:
    case 0x84:
        kc = (char *)"3";
        if (k == 0x04)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x08:
    case 0x88:
        kc = (char *)"7";
        if (k == 0x08)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x0C:
    case 0x8C:
        kc = (char *)"-";
        if (k == 0x0C)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x10:
        if (last_key == 0xE0)
            kc = (char *)"ptrack";
        else
            kc = (char *)"q";
        k_s.released = false;
        break;

    case 0x14:
    case 0x94:
        kc = (char *)"t";
        if (k == 0x14)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x18:
    case 0x98:
        kc = (char *)"o";
        if (k == 0x18)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x1C:
    case 0x9C:
        if (last_key == 0xE0)
            kc = (char *)"enter";
        else
            kc = (char *)"enter";
        if (k == 0x1C)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x20:
    case 0xA0:
        if (last_key == 0xE0)
            kc = (char *)"mute";
        else
            kc = (char *)"d";
        if (k == 0x20)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x24:
    case 0xA4:
        if (last_key == 0xE0)
            kc = (char *)"stop";
        else
            kc = (char *)"j";
        if (k == 0x24)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x28:
    case 0xA8:
        kc = (char *)"\\";
        if (k == 0x28)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x2C:
    case 0xAC:
        kc = (char *)"z";
        if (k == 0x2C)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x30:
    case 0xB0:
        if (last_key == 0xE0)
            kc = (char *)"vol_up";
        else
            kc = (char *)"b";
        if (k == 0x30)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x34:
    case 0xB4:
        kc = (char *)".";
        if (k == 0x34)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x38:
    case 0xB8:
        if (last_key == 0xE0)
            kc = (char *)"ralt";
        else
            kc = (char *)"lalt";
        if (k == 0x38)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x3C:
    case 0xBC:
        kc = (char *)"f2";
        if (k == 0x3C)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x40:
    case 0xC0:
        kc = (char *)"f6";
        if (k == 0x40)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x44:
    case 0xC4:
        kc = (char *)"f10";
        if (k == 0x44)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x48:
    case 0xC8:
        if (last_key == 0xE0)
            kc = (char *)"mouse_up";
        else
            kc = (char *)"8";
        if (k == 0x48)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x4C:
    case 0xCC:
        kc = (char *)"5";
        if (k == 0x4C)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x50:
    case 0xD0:
        if (last_key == 0xE0)
            kc = (char *)"mouse_dwn";
        else
            kc = (char *)"2";
        if (k == 0x50)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x57:
    case 0xD7:
        kc = (char *)"f11";
        if (k == 0x57)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x58:
    case 0xD8:
        kc = (char *)"f12";
        if (k == 0x58)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x01:
    case 0x81:
        kc = (char *)"esc";
        if (k == 0x01)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x90:
        if (last_key == 0xE0)
            kc = (char *)"prev_track";
        else
            kc = (char *)"1";
        k_s.released = true;
        break;

    case 0x19:
    case 0x99:
        if (last_key == 0xE0)
            kc = (char *)"n_track";
        else
            kc = (char *)"p";
        if (k == 0x19)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x2E:
    case 0xAE:
        if (last_key == 0xE0)
            kc = (char *)"vol_dwn";
        else
            kc = (char *)"c";
        if (k == 0x2E)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x35:
    case 0xB5:
        if (last_key == 0xE0)
            kc = (char *)"/";
        else
            kc = (char *)"/";
        if (k == 0x35)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x47:
    case 0xC7:
        if (last_key == 0xE0)
            kc = (char *)"home";
        else
            kc = (char *)"7";
        if (k == 0x47)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x4D:
    case 0xCD:
        if (last_key == 0xE0)
            kc = (char *)"mouse_r";
        else
            kc = (char *)"6";
        if (k == 0x4D)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x5B:
    case 0xDB:
        if (last_key == 0xE0)
            kc = (char *)"lgui";
        if (k == 0x5B)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x5C:
    case 0xDC:
        if (last_key == 0xE0)
            kc = (char *)"rgui";
        if (k == 0x5C)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x63:
    case 0xE3:
        if (last_key == 0xE0)
            kc = (char *)"wake";
        if (k == 0x63)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x65:
    case 0xE5:
        if (last_key == 0xE0)
            kc = (char *)"www_search";
        if (k == 0x65)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x69:
        if (last_key == 0xE0)
            kc = (char *)"www_fwd";
        if (k == 0x69)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x68:
    case 0xE8:
        if (last_key == 0xE0)
            kc = (char *)"www_stop";
        if (k == 0x68)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x6C:
    case 0xEC:
        if (last_key == 0xE0)
            kc = (char *)"email";
        if (k == 0x6C)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x09:
    case 0x89:
        kc = (char *)"8";
        if (k == 0x09)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x0D:
    case 0x8D:
        kc = (char *)"=";
        if (k == 0x0D)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x11:
    case 0x91:
        kc = (char *)"w";
        if (k == 0x11)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x15:
    case 0x95:
        kc = (char *)"y";
        if (k == 0x15)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x1D:
    case 0x9D:
        if (last_key == 0xE0)
            kc = (char *)"l_ctrl";
        else
            kc = (char *)"r_ctrl";
        if (k == 0x1D)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x21:
    case 0xA1:
        if (last_key == 0xE0)
            kc = (char *)"calc";
        else
            kc = (char *)"f";
        if (k == 0x21)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x25:
    case 0xA5:
        kc = (char *)"k";
        if (k == 0x25)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x29:
    case 0xA9:
        kc = (char *)"`";
        if (k == 0x29)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x2D:
    case 0xAD:
        kc = (char *)"x";
        if (k == 0x2D)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x31:
    case 0xB1:
        if (last_key == 0xE0)
            kc = (char *)"n";
        else
            kc = (char *)"f7";
        if (k == 0x31)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x39:
    case 0xB9:
        kc = (char *)" ";
        if (k == 0x39)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x3D:
    case 0xBD:
        kc = (char *)"f3";
        if (k == 0x3D)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x45:
    case 0xC5:
        kc = (char *)"nlock";
        if (k == 0x45)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x49:
    case 0xC9:
        if (last_key == 0xE0)
            kc = (char *)"9";
        else
            kc = (char *)"pg_up";
        if (k == 0x49)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x51:
    case 0xD1:
        if (last_key == 0xE0)
            kc = (char *)"3";
        else
            kc = (char *)"pg_dwn";
        if (k == 0x51)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x5D:
        if (last_key == 0xE0)
            kc = (char *)"apps";
        if (k == 0x5D)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x02:
    case 0x82:
        kc = (char *)"1";
        if (k == 0x02)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x06:
    case 0x86:
        kc = (char *)"5";
        if (k == 0x06)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x0A:
    case 0x8A:
        kc = (char *)"9";
        if (k == 0x0A)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x0E:
    case 0x8E:
        kc = (char *)"bkspc";
        if (k == 0x0E)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x12:
    case 0x92:
        kc = (char *)"e";
        if (k == 0x12)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x16:
    case 0x96:
        kc = (char *)"u";
        if (k == 0x16)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x1A:
    case 0x9A:
        kc = (char *)"[";
        if (k == 0x1A)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x1E:
    case 0x9E:
        kc = (char *)"a";
        if (k == 0x1A)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x22:
    case 0xA2:
        if (last_key == 0xE0)
            kc = (char *)"play";
        else
            kc = (char *)"g";
        if (k == 0x22)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x26:
    case 0xA6:
        kc = (char *)"l";
        if (k == 0x26)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x2A:
    case 0xAA:
        kc = (char *)"l_shift";
        if (k == 0x2A)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x32:
    case 0xB2:
        if (last_key == 0xE0)
            kc = (char *)"www_home";
        else
            kc = (char *)"m";
        if (k == 0x32)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x36:
    case 0xB6:
        kc = (char *)"r_shift";
        if (k == 0x36)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x3A:
    case 0xBA:
        kc = (char *)"c_lock";
        if (k == 0x3A)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x3E:
    case 0xBE:
        kc = (char *)"f4";
        if (k == 0x3E)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x42:
    case 0xC2:
        kc = (char *)"f8";
        if (k == 0x42)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x46:
    case 0xC6:
        kc = (char *)"s_lock";
        if (k == 0x46)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x4A:
    case 0xCA:
        kc = (char *)"-";
        if (k == 0x4A)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x4E:
    case 0xCE:
        kc = (char *)"+";
        if (k == 0x4E)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x52:
    case 0xD2:
        if (last_key == 0xE0)
            kc = (char *)"insert";
        if (k == 0x52)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x5E:
        if (last_key == 0xE0)
            kc = (char *)"pwr";
        if (k == 0x5E)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x66:
        if (last_key == 0xE0)
            kc = (char *)"www_fav";
        if (k == 0x66)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x6A:
        if (last_key == 0xE0)
            kc = (char *)"www_back";
        if (k == 0x6A)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x03:
    case 0x83:
        kc = (char *)"2";
        if (k == 0x03)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x07:
    case 0x87:
        kc = (char *)"6";
        if (k == 0x07)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x0B:
    case 0x8B:
        kc = (char *)"0";
        if (k == 0x0B)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x0F:
    case 0x8F:
        kc = (char *)"tab";
        if (k == 0x0F)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x13:
    case 0x93:
        kc = (char *)"r";
        if (k == 0x13)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x17:
    case 0x97:
        kc = (char *)"i";
        if (k == 0x17)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x1B:
    case 0x9B:
        kc = (char *)"]";
        if (k == 0x1B)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x1F:
    case 0x9F:
        kc = (char *)"s";
        if (k == 0x1F)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x23:
    case 0xA3:
        kc = (char *)"h";
        if (k == 0x23)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x27:
    case 0xA7:
        kc = (char *)";";
        if (k == 0x27)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x2B:
    case 0xAB:
        kc = (char *)"\\";
        if (k == 0x2B)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x2F:
    case 0xAF:
        kc = (char *)"v";
        if (k == 0x2F)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x33:
    case 0xB3:
        kc = (char *)",";
        if (k == 0x33)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x37:
    case 0xB7:
        kc = (char *)"*";
        if (k == 0x37)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x3B:
    case 0xBB:
        kc = (char *)"f1";
        if (k == 0x3B)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x3F:
    case 0xBF:
        kc = (char *)"f5";
        if (k == 0x3F)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x43:
    case 0xC3:
        kc = (char *)"f9";
        if (k == 0x43)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x4B:
    case 0xCB:
        if (last_key == 0xE0)
            kc = (char *)"4";
        else
            kc = (char *)"mouse_l";
        if (k == 0x4B)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x4F:
    case 0xCF:
        if (last_key == 0xE0)
            kc = (char *)"end";
        else
            kc = (char *)"1";
        if (k == 0x4F)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x53:
    case 0xD3:
        kc = (char *)"delete";
        if (k == 0x53)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x67:
    case 0xE7:
        kc = (char *)"www_refresh";
        if (k == 0x67)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x6B:
    case 0xEB:
        kc = (char *)"my_computer";
        if (k == 0x67)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    case 0x05:
    case 0x85:
        kc = (char *)"4";
        if (k == 0x05)
            k_s.released = false;
        else
            k_s.released = true;
        break;

    default:
        break;
    }

    if (update_last_key)
        last_key = k;
    k_s.m_key = kc;

    return k_s;
}

// Get the current pressed key, returns a null character if nothing was found
struct key_t get_key()
{
    // Key scancode
    uint8_t k = 0;

    // Key struct
    struct key_t k_s;

    k_s.i_key = k;
    k_s.m_key = (char *)"\0";
    k_s.last_key = 0;

    k = inb(0x60);

    struct key_t temp = key_from_uint8_t(k, true);
    if (temp.m_key == (char *)"\0")
    {
        k_s.m_key = (char *)"\0";
        return k_s;
    }
    else
        return temp;

    return k_s;
}