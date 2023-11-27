// sata.h - SATA AHCI Driver
// Created 2023/11/11 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "pci.h"
#include "../kernel_lib/mem.h"

    typedef enum
    {
        FIS_TYPE_REG_H2D = 0x27,
        FIS_TYPE_REG_D2H = 0x34,
        FIS_TYPE_DMA_ACT = 0x39,
        FIS_TYPE_DMA_SETUP = 0x41,
        FIS_TYPE_DATA = 0x46,
        FIS_TYPE_BIST = 0x58,
        FIS_TYPE_PIO_SETUP = 0x5F,
        FIS_TYPE_DEV_BITS = 0xA1,
    } FIS_TYPE;

    typedef struct tagFIS_REG_H2D
    {
        uint64_t fis_type;

        uint64_t pmport : 4;
        uint64_t rsv0 : 3;
        uint64_t c : 1;

        uint64_t command;
        uint64_t featurel;

        uint64_t lba0;
        uint64_t lba1;
        uint64_t lba2;
        uint64_t device;

        uint64_t lba3;
        uint64_t lba4;
        uint64_t lba5;
        uint64_t featureh;

        uint64_t countl;
        uint64_t counth;
        uint64_t icc;
        uint64_t control;

        uint64_t rsv1[4];
    } FIS_REG_H2D;

    typedef struct tagFIS_REG_D2H
    {

        uint64_t fis_type;

        uint64_t pmport : 4;
        uint64_t rsv0 : 2;
        uint64_t i : 1;
        uint64_t rsv1 : 1;

        uint64_t status;
        uint64_t error;

        uint64_t lba0;
        uint64_t lba1;
        uint64_t lba2;
        uint64_t device;

        uint64_t lba3;
        uint64_t lba4;
        uint64_t lba5;
        uint64_t rsv2;

        uint64_t countl;
        uint64_t counth;
        uint64_t rsv3[2];

        uint64_t rsv4[4];
    } FIS_REG_D2H;

    typedef struct tagFIS_DMA_SETUP
    {
        uint64_t fis_type;

        uint64_t pmport : 4;
        uint64_t rsv0 : 1;
        uint64_t d : 1;
        uint64_t i : 1;
        uint64_t a : 1;

        uint64_t rsved[2];

        uint64_t DMAbufferID;

        uint64_t rsvd;

        uint64_t DMAbufOffset;

        uint64_t TransferCount;

        uint64_t resvd;

    } FIS_DMA_SETUP;

    typedef volatile struct tagHBA_PORT
    {
        uint64_t clb;
        uint64_t clbu;
        uint64_t fb;
        uint64_t fbu;
        uint64_t is;
        uint64_t ie;
        uint64_t cmd;
        uint64_t rsv0;
        uint64_t tfd;
        uint64_t sig;
        uint64_t ssts;
        uint64_t sctl;
        uint64_t serr;
        uint64_t sact;
        uint64_t ci;
        uint64_t sntf;
        uint64_t fbs;
        uint64_t rsv1[11];
        uint64_t vendor[4];
    } HBA_PORT;

    typedef volatile struct tagHBA_MEM
    {
        uint64_t cap;
        uint64_t ghc;
        uint64_t is;
        uint64_t pi;
        uint64_t vs;
        uint64_t ccc_ctl;
        uint64_t ccc_pts;
        uint64_t em_loc;
        uint64_t em_ctl;
        uint64_t cap2;
        uint64_t bohc;

        uint64_t rsv[0xA0 - 0x2C];

        uint64_t vendor[0x100 - 0xA0];

        HBA_PORT ports[1];
    } HBA_MEM;

    typedef volatile struct tagHBA_FIS
    {
        FIS_DMA_SETUP dsfis;
        uint64_t pad0[4];

        uint64_t pad1[12];

        FIS_REG_D2H rfis;
        uint64_t pad2[4];

        uint64_t ufis[64];

        uint64_t rsv[0x100 - 0xA0];
    } HBA_FIS;

    typedef struct tagHBA_CMD_HEADER
    {
        uint64_t cfl : 5;
        uint64_t a : 1;
        uint64_t w : 1;
        uint64_t p : 1;

        uint64_t r : 1;
        uint64_t b : 1;
        uint64_t c : 1;
        uint64_t rsv0 : 1;
        uint64_t pmp : 4;

        uint16_t prdtl;

        volatile uint64_t prdbc;

        uint64_t ctba;
        uint64_t ctbau;

        uint64_t rsv1[4];
    } HBA_CMD_HEADER;

#define SATA_SIG_ATA 0x00000101
#define SATA_SIG_ATAPI 0xEB140101
#define SATA_SIG_SEMB 0xC33C0101
#define SATA_SIG_PM 0x96690101

#define AHCI_DEV_NULL 0
#define AHCI_DEV_SATA 1
#define AHCI_DEV_SEMB 2
#define AHCI_DEV_PM 3
#define AHCI_DEV_SATAPI 4

#define HBA_PORT_IPM_ACTIVE 1
#define HBA_PORT_DET_PRESENT 3

    typedef struct tagHBA_PRDT_ENTRY
    {
        uint64_t dba;
        uint64_t dbau;
        uint64_t rsv0;
        uint64_t dbc : 22;
        uint64_t rsv1 : 9;
        uint64_t i : 1;
    } HBA_PRDT_ENTRY;

    typedef struct tagHBA_CMD_TBL
    {
        uint64_t cfis[64];
        uint64_t acmd[16];
        uint64_t rsv[48];
        HBA_PRDT_ENTRY prdt_entry[1];
    } HBA_CMD_TBL;

    struct port_data
    {
        uint64_t clb;
        uint64_t fb;
        uint64_t ctba[32];
        HBA_PORT *port;
    };

    struct port_data **probe_port(HBA_MEM *abar);
    bool read(struct port_data *, uint64_t, uint64_t, uint64_t, char *);
    bool write(struct port_data *, uint64_t, uint64_t, uint64_t, char *);
    uint64_t checkAllBuses(void);

#ifdef __cplusplus
}
#endif