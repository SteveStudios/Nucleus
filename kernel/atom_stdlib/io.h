// io.h - Terminal and input/output utilituies
// Created 2023/7/11 by Stephen Byrne

// Possible colors for terminal text
enum {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    PURPLE = 5,
    BROWN = 6, 
    GRAY = 7,
    GRAY_DARK = 8,
    BLUE_LIGHT = 9,
    GREEN_LIGHT = 10,
    CYAN_LIGHT = 11,
    RED_LIGHT = 12,
    PURPLE_LIGHT = 13,
    YELLOW = 14,
    WHITE = 15
};

// Write a string to video memory, default color is white
inline void println(const char* str, int col = 15) {
    volatile char *vmem = (volatile char*)0xB8000;
    while (*str != 0) {
        *vmem++ = *str++;
        *vmem++ = col;
    }
}