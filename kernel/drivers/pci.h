// pci.h - PCI Driver
// Created 2023/11/12 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "../contrib/liballoc/liballoc.h"

    struct _pci_driver;

    typedef struct
    {
        uint32_t vendor;
        uint32_t device;
        uint32_t func;
        struct _pci_driver *driver;
    } pci_device;

    typedef struct
    {
        uint32_t vendor;
        uint32_t device;
        uint32_t func;
    } pci_device_id;

    typedef struct _pci_driver
    {
        pci_device_id *table;
        char *name;
        uint8_t (*init_one)(pci_device *);
        uint8_t (*init_driver)(void);
        uint8_t (*exit_driver)(void);
    } pci_driver;

    void pci_init();
    void pci_proc_dump(uint8_t *);

#ifdef __cplusplus
}
#endif