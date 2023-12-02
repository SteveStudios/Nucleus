// pci.h - PCI Driver
// Created 2023/11/12 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "../kernel_lib/ports.h"
#include "../kernel_lib/io.h"
#include "../lib/liballoc/liballoc.h"

    struct _pci_driver;

    typedef struct
    {
        uint32_t vendor;
        uint32_t device;
        uint32_t func;
        uint32_t slot;
        uint32_t bus;
    } pci_device;

    void pci_init();
    void pci_proc_dump(uint8_t *);
    uint32_t pci_read_word(uint32_t bus, uint32_t slot, uint32_t func, uint32_t offset);

#ifdef __cplusplus
}
#endif