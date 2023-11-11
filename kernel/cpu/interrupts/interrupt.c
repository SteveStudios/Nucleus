// interrupt.c - Interrupt handler
// Created 2023/7/21 by Stephen Byrne

#include "interrupt.h"

// Called from (cpu/interrupts/asm/irq_helper.asm)
void handle_interrupt(int irq_n)
{
    if (inb(0x60) == 0xE0)
        last_key = 0xE0;

    switch (irq_n)
    {
        case 1:
            handle_keyboard();
            break;
        case 14:
            println("[INFO]: Storage Device Ready");
            break;
    }

    if (irq_n >= 8)
        outb(0xA0, 0x20);
    outb(0x20, 0x20);
}

void NumbertoCharacter(int n)
{
    int rev = 0, r = 0;
 
    // To calculate the reverse of the number
    while (n > 0) {
 
        // The remainder will give the last digit of the number
        r = n % 10;
        rev = rev * 10 + r;
        n = n / 10;
    }
 
    while (rev > 0) {
        r = rev % 10;

        switch (r) {
        case 1:
            println((char*)"1");
            break;
        case 2:
            println((char*)"2");
            break;
        case 3:
            println((char*)"3");
            break;
        case 4:
            println((char*)"4");
            break;
        case 5:
            println((char*)"5");
            break;
        case 6:
            println((char*)"6");
            break;
        case 7:
            println((char*)"7");
            break;
        case 8:
            println((char*)"8");
            break;
        case 9:
            println((char*)"9");
            break;
        case 0:
            println((char*)"0");
            break;
        default:
            println((char*)"invalid ");
            break;
        }
 
        rev = rev / 10;
    }
}