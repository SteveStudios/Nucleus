// hdd_pio.h - HDD PIO Driver
// Created 2023/7/10 by Stephen Byrne

#include "hddpio.h"

// Read from a sector
void read_sector(int sector, unsigned char block_addr) {
    outb(0x1F1, 0x00);
    outb(0x1F2, sector);
    outb(0x1F3, block_addr);
    outb(0x1F4, block_addr >> 8);
    outb(0x1F5, block_addr >> 16);
    outb(0x1F7, 0x20);
}