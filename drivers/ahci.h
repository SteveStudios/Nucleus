// sata.h - SATA AHCI Driver
// Created 2023/11/11 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
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
        uint32_t fis_type;

        uint32_t pmport : 4;
        uint32_t rsv0 : 3;
        uint32_t c : 1;

        uint32_t command;
        uint32_t featurel;

        uint32_t lba0;
        uint32_t lba1;
        uint32_t lba2;
        uint32_t device;

        uint32_t lba3;
        uint32_t lba4;
        uint32_t lba5;
        uint32_t featureh;

        uint32_t countl;
        uint32_t counth;
        uint32_t icc;
        uint32_t control;

        uint32_t rsv1[4];
    } FIS_REG_H2D;

    typedef struct tagFIS_REG_D2H
    {

        uint32_t fis_type;

        uint32_t pmport : 4;
        uint32_t rsv0 : 2;
        uint32_t i : 1;
        uint32_t rsv1 : 1;

        uint32_t status;
        uint32_t error;

        uint32_t lba0;
        uint32_t lba1;
        uint32_t lba2;
        uint32_t device;

        uint32_t lba3;
        uint32_t lba4;
        uint32_t lba5;
        uint32_t rsv2;

        uint32_t countl;
        uint32_t counth;
        uint32_t rsv3[2];

        uint32_t rsv4[4];
    } FIS_REG_D2H;

    typedef struct tagFIS_DMA_SETUP
    {
        uint32_t fis_type;

        uint32_t pmport : 4;
        uint32_t rsv0 : 1;
        uint32_t d : 1;
        uint32_t i : 1;
        uint32_t a : 1;

        uint32_t rsved[2];

        uint64_t DMAbufferID;

        uint32_t rsvd;

        uint32_t DMAbufOffset;

        uint32_t TransferCount;

        uint32_t resvd;

    } FIS_DMA_SETUP;

    typedef volatile struct tagHBA_PORT
    {
        uint32_t clb;
        uint32_t clbu;
        uint32_t fb;
        uint32_t fbu;
        uint32_t is;
        uint32_t ie;
        uint32_t cmd;
        uint32_t rsv0;
        uint32_t tfd;
        uint32_t sig;
        uint32_t ssts;
        uint32_t sctl;
        uint32_t serr;
        uint32_t sact;
        uint32_t ci;
        uint32_t sntf;
        uint32_t fbs;
        uint32_t rsv1[11];
        uint32_t vendor[4];
    } HBA_PORT;

    typedef volatile struct tagHBA_MEM
    {
        uint32_t cap;
        uint32_t ghc;
        uint32_t is;
        uint32_t pi;
        uint32_t vs;
        uint32_t ccc_ctl;
        uint32_t ccc_pts;
        uint32_t em_loc;
        uint32_t em_ctl;
        uint32_t cap2;
        uint32_t bohc;

        uint32_t rsv[0xA0 - 0x2C];

        uint32_t vendor[0x100 - 0xA0];

        HBA_PORT ports[1];
    } HBA_MEM;

    typedef volatile struct tagHBA_FIS
    {
        FIS_DMA_SETUP dsfis;
        uint32_t pad0[4];

        uint32_t pad1[12];

        FIS_REG_D2H rfis;
        uint32_t pad2[4];

        uint32_t ufis[64];

        uint32_t rsv[0x100 - 0xA0];
    } HBA_FIS;

    typedef struct tagHBA_CMD_HEADER
    {
        uint32_t cfl : 5;
        uint32_t a : 1;
        uint32_t w : 1;
        uint32_t p : 1;

        uint32_t r : 1;
        uint32_t b : 1;
        uint32_t c : 1;
        uint32_t rsv0 : 1;
        uint32_t pmp : 4;

        uint16_t prdtl;

        volatile uint32_t prdbc;

        uint32_t ctba;
        uint32_t ctbau;

        uint32_t rsv1[4];
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
        uint32_t dba;
        uint32_t dbau;
        uint32_t rsv0;
        uint32_t dbc : 22;
        uint32_t rsv1 : 9;
        uint32_t i : 1;
    } HBA_PRDT_ENTRY;

    typedef struct tagHBA_CMD_TBL
    {
        uint32_t cfis[64];
        uint32_t acmd[16];
        uint32_t rsv[48];
        HBA_PRDT_ENTRY prdt_entry[1];
    } HBA_CMD_TBL;

    struct port_data
    {
        void *clb;
        void *fb;
        void *ctba[32];
        HBA_PORT *port;
    };

    struct port_data **probe_port(HBA_MEM *abar);
    bool read(struct port_data *, uint32_t, uint32_t, uint32_t, char *);
    bool write(struct port_data *, uint32_t, uint32_t, uint32_t, char *);

#ifdef __cplusplus
}
#endif