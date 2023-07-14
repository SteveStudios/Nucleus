// idt.h - Interrupt descriptor table and ISR utilities
// Created 2023/7/11 by Stephen Byrne

#pragma once

#include <stdint.h>
#include "../../stdlib/io.h"
#include "../../stdlib/ports.h"

#ifdef __cplusplus
extern "C" {
#endif

void idt_setgate(int gate, uint32_t val);
void idt_init();

#ifdef __cplusplus
}
#endif