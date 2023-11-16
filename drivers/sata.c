// sata.c - SATA AHCI Driver
// Created 2023/11/11 by Stephen Byrne

#include "sata.h"

HBA_MEM *glob_abar;

static int check_type(HBA_PORT *port)
{
	int32_t ssts = port->ssts;

	int8_t ipm = (ssts >> 8) & 0x0F;
	int8_t det = ssts & 0x0F;

	if (det != HBA_PORT_DET_PRESENT)
		return AHCI_DEV_NULL;
	if (ipm != HBA_PORT_IPM_ACTIVE)
		return AHCI_DEV_NULL;

	switch (port->sig)
	{
	case SATA_SIG_ATAPI:
		return AHCI_DEV_SATAPI;
	case SATA_SIG_SEMB:
		return AHCI_DEV_SEMB;
	case SATA_SIG_PM:
		return AHCI_DEV_PM;
	default:
		return AHCI_DEV_SATA;
	}
}

#define AHCI_BASE 0x400000

#define HBA_PxCMD_ST 0x0001
#define HBA_PxCMD_FRE 0x0010
#define HBA_PxCMD_FR 0x4000
#define HBA_PxCMD_CR 0x8000

void port_rebase(struct port_data *port, int portno, struct port_data *pdata)
{
	stop_cmd(port);

	port->clb = AHCI_BASE + (portno << 10);
	port->port->clbu = 0;
	pdata->clb = port->clb;

	memset((void *)(port->clb), 0, 1024);

	port->fb = AHCI_BASE + (32 << 10) + (portno << 8);
	port->port->fbu = 0;
	pdata->fb = port->fb;
	memset((void *)(port->fb), 0, 256);

	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER *)(port->clb);
	for (int i = 0; i < 32; i++)
	{
		cmdheader[i].prdtl = 8;
		cmdheader[i].ctba = AHCI_BASE + (40 << 10) + (portno << 13) + (i << 8);
		cmdheader[i].ctbau = 0;

		pdata->ctba[i] = cmdheader[i].ctba;

		memset((void *)cmdheader[i].ctba, 0, 256);
	}

	pdata->port = port;
	start_cmd(port);
}

void start_cmd(struct port_data *port)
{
	while (port->port->cmd & HBA_PxCMD_CR)
		;

	port->port->cmd |= HBA_PxCMD_FRE;
	port->port->cmd |= HBA_PxCMD_ST;
}

void stop_cmd(struct port_data *port)
{
	port->port->cmd &= ~HBA_PxCMD_ST;
	port->port->cmd &= ~HBA_PxCMD_FRE;

	while (1)
	{
		if (port->port->cmd & HBA_PxCMD_FR)
			continue;
		if (port->port->cmd & HBA_PxCMD_CR)
			continue;
		break;
	}
}

#define ATA_DEV_BUSY 0x80
#define ATA_DEV_DRQ 0x08

int find_cmdslot(HBA_PORT *port)
{
	uint32_t slots = (port->sact | port->ci);
	int cmdslots = (glob_abar->cap & 0x0f00) >> 8;
	for (int i = 0; i < cmdslots; i++)
	{
		if ((slots & 1) == 0)
			return i;
		slots >>= 1;
	}
	return -1;
}

bool write(struct port_data *port, uint32_t startl, uint32_t starth, uint32_t count, char *buf)
{
	port->port->is = 0xffff;
	int slot = find_cmdslot(port->port);
	if (slot == -1)
		return 0;
	uint64_t addr = 0;
	addr = (((addr | port->port->clbu) << 32) | port->port->clb);

	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER *)(KERNEL_LOC + addr);

	cmdheader += slot;
	cmdheader->cfl = sizeof(FIS_REG_H2D) / sizeof(uint32_t);
	cmdheader->w = 1;
	cmdheader->c = 1;
	cmdheader->p = 1;
	cmdheader->prdtl = (uint16_t)((count - 1) >> 4) + 1;
	cmdheader->prdtl = (uint16_t)((count - 1) >> 4) + 1;
	addr = 0;
	addr = (((addr | cmdheader->ctbau) << 32) | cmdheader->ctba);

	HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL *)(KERNEL_LOC + addr);
	int i = 0;

	for (i = 0; i < cmdheader->prdtl - 1; i++)
	{
		cmdtbl->prdt_entry[i].dba = (uint32_t)(*buf & 0xFFFFFFFF);
		cmdtbl->prdt_entry[i].dbau = (uint32_t)((*buf << 32) & 0xFFFFFFFF);
		cmdtbl->prdt_entry[i].dbc = 8 * 1024 - 1;
		cmdtbl->prdt_entry[i].i = 0;
		buf += 4 * 1024;
		count -= 16;
	}
	cmdtbl->prdt_entry[i].dba = (uint32_t)(*buf & 0xFFFFFFFF);
	cmdtbl->prdt_entry[i].dbau = (uint32_t)((*buf << 32) & 0xFFFFFFFF);
	cmdtbl->prdt_entry[i].dbc = count << 9;
	cmdtbl->prdt_entry[i].i = 0;

	FIS_REG_H2D *cmdfis = (FIS_REG_H2D *)(&cmdtbl->cfis);
	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->c = 1;
	cmdfis->command = 0x35;

	cmdfis->lba0 = (uint8_t)startl;
	cmdfis->lba1 = (uint8_t)(startl >> 8);
	cmdfis->lba2 = (uint8_t)(startl >> 16);
	cmdfis->device = 1 << 6;

	cmdfis->lba3 = (uint8_t)(startl >> 24);
	cmdfis->lba4 = (uint8_t)starth;
	cmdfis->lba5 = (uint8_t)(starth >> 8);

	cmdfis->countl = count & 0xff;
	cmdfis->counth = count >> 8;

	port->port->ci = 1;
	while (1)
	{
		if ((port->port->ci & (1 << slot)) == 0)
			break;
		if (port->port->is & (1 << 30))
		{
			println("[SATA] Error writing to Disk");
			return 0;
		}
	}
	if (port->port->is & (1 << 30))
	{
		println("[SATA] Error writing to Disk");
		return 0;
	}
	return 1;
}

bool read(struct port_data *pdata, uint32_t startl, uint32_t starth, uint32_t count, char *buf)
{
	pdata->port->is = (uint32_t)-1;
	int spin = 0;
	int slot = find_cmdslot(pdata->port);
	if (slot == -1)
		return 0;

	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER *)pdata->clb;
	cmdheader += slot;
	cmdheader->cfl = sizeof(FIS_REG_H2D) / sizeof(uint32_t);
	cmdheader->w = 0;
	cmdheader->prdtl = (uint16_t)((count - 1) >> 4) + 1;

	HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL *)pdata->ctba[slot];

	int i;
	for (i = 0; i < cmdheader->prdtl - 1; i++)
	{
		cmdtbl->prdt_entry[i].dba = (uint32_t)(*buf & 0xffffffff);
		cmdtbl->prdt_entry[i].dbau = (uint32_t)(((*buf) >> 32) & 0xffffffff);
		cmdtbl->prdt_entry[i].dbc = 8 * 1024;
		cmdtbl->prdt_entry[i].i = 1;
		buf += 4 * 1024;
		count -= 16;
	}

	cmdtbl->prdt_entry[i].dba = (uint32_t)(*buf & 0xffffffff);
	cmdtbl->prdt_entry[i].dbau = (uint32_t)((*buf >> 32) & 0xffffffff);
	cmdtbl->prdt_entry[i].dbc = count << 9;
	cmdtbl->prdt_entry[i].i = 1;

	FIS_REG_H2D *cmdfis = (FIS_REG_H2D *)(&cmdtbl->cfis);

	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->c = 1;
	cmdfis->command = 0x25;

	cmdfis->lba0 = (uint8_t)startl;
	cmdfis->lba1 = (uint8_t)(startl >> 8);
	cmdfis->lba2 = (uint8_t)(startl >> 16);
	cmdfis->device = 1 << 6;

	cmdfis->lba3 = (uint8_t)(startl >> 24);
	cmdfis->lba4 = (uint8_t)starth;
	cmdfis->lba5 = (uint8_t)(starth >> 8);

	cmdfis->countl = (count & 0xff);
	cmdfis->counth = (count >> 8);

	while ((pdata->port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) && spin < 1000000)
	{
		spin++;
	}
	if (spin == 1000000)
	{
		println("[SATA] Port is idle");
		return 0;
	}

	pdata->port->ci = (1 << slot);

	while (true)
	{
		if ((pdata->port->ci & (1 << slot)) == 0)
			break;
		if (pdata->port->is & (1 << 30))
		{
			println("[SATA] Error writing to Disk");
			return 0;
		}
	}

	if (pdata->port->is & (1 << 30))
	{
		println("[SATA] Error writing to Disk");
		return 0;
	}

	return 1;
}

struct port_data **probe_port(HBA_MEM *abar)
{
	glob_abar = abar;

	uint32_t pi = abar->pi;
	int i = 0;

	struct port_data **pdtable = malloc(32 * sizeof(void *));

	while (i < 32)
	{
		if (pi & 1)
		{
			int dt = check_type((HBA_PORT *)&abar->ports[i]);
			if (dt == AHCI_DEV_SATA)
			{
				pdtable[i] = malloc(sizeof(struct port_data));
				println("[SATA] Device found");
				port_rebase(abar->ports, i, pdtable[i]);
			}
		}
		pi >>= 1;
		i++;
	}
	return pdtable;
}