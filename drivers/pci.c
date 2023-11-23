// pci.c - PCI Driver
// Created 2023/11/12 by Stephen Byrne

#include "pci.h"

pci_device **pci_devices;
uint32_t devs = 0;

pci_driver **pci_drivers;
uint32_t drivs = 0;

void add_pci_device(pci_device *pdev)
{
    pci_devices[devs] = pdev;
    devs++;
    return;
}

uint32_t pci_read_word(uint32_t bus, uint32_t slot, uint32_t func, uint32_t offset)
{
    uint64_t address;
    uint64_t lbus = (uint64_t)bus;
    uint64_t lslot = (uint64_t)slot;
    uint64_t lfunc = (uint64_t)func;
    uint32_t tmp = 0;
    address = (uint64_t)((lbus << 16) | (lslot << 11) |
                         (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));
    outb(0xCF8, address);
    tmp = (uint32_t)((inb(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
}

uint32_t getVendorID(uint32_t bus, uint32_t device, uint32_t function)
{
    uint32_t r0 = pci_read_word(bus, device, function, 0);
    return r0;
}

uint32_t getDeviceID(uint32_t bus, uint32_t device, uint32_t function)
{
    uint32_t r0 = pci_read_word(bus, device, function, 2);
    return r0;
}

uint32_t getClassId(uint32_t bus, uint32_t device, uint32_t function)
{
    uint32_t r0 = pci_read_word(bus, device, function, 0xA);
    return (r0 & ~0x00FF) >> 8;
}

uint32_t getSubClassId(uint32_t bus, uint32_t device, uint32_t function)
{
    uint32_t r0 = pci_read_word(bus, device, function, 0xA);
    return (r0 & ~0xFF00);
}

void pci_probe()
{
    for (int bus = 0; bus < 256; bus++)
    {
        for (int slot = 0; slot < 32; slot++)
        {
            for (int function = 0; function < 8; function++)
            {
                bool do_continue = false;

                uint32_t vendor = getVendorID(bus, slot, function);
                if (vendor == 0xFFFF)
                    continue;

                uint32_t device = getDeviceID(bus, slot, function);
                for (int i = 0; i < devs; i++)
                {
                    if (pci_devices[i]->device == device && pci_devices[i]->vendor == vendor)
                    {
                        do_continue = true;
                        break;
                    }
                }

                if (do_continue)
                    continue;

                println("[PCI] Device found");

                pci_device *pdev = (pci_device *)malloc(sizeof(pci_device));
                pdev->vendor = vendor;
                pdev->device = device;
                pdev->func = function;
                pdev->driver = 0;

                add_pci_device(pdev);
            }
        }
    }
}

uint32_t pciCheckVendor(uint32_t bus, uint32_t slot)
{
    uint32_t vendor, device;
    if ((vendor = pci_read_word(bus, slot, 0, 0)) != 0xFFFF)
        device = pci_read_word(bus, slot, 0, 2);
    return (vendor);
}

void pci_init()
{
    devs = drivs = 0;
    pci_devices = malloc(32 * sizeof(pci_device));
    pci_drivers = malloc(32 * sizeof(pci_driver));
    pci_probe();
}

void pci_register_driver(pci_driver *driv)
{
    pci_drivers[drivs] = driv;
    drivs++;
    return;
}

void pci_proc_dump(uint8_t *buffer)
{
    for (int i = 0; i < devs; i++)
    {
        pci_device *pci_dev = pci_devices[i];
    }
}