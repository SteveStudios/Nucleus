// gdt.h - GDT (Global Descriptor Table) manager
// Created 2023/7/20 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct
{
	uint16_t limit;
	uint64_t base;
} __attribute__((__packed__)) gdtr_t;

extern void reload_segment_registers();
void gdt_init();

#ifdef __cplusplus
}
#endif