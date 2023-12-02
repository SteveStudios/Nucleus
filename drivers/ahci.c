// sata.c - SATA AHCI Driver
// Created 2023/11/11 by Stephen Byrne

#include "ahci.h"

HBA_MEM *glob_abar;

static int check_type(HBA_PORT *port)
{
	uint32_t ssts = port->ssts;

	char ipm = (ssts >> 8) & 0x0F;
	char det = ssts & 0x0F;

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

void start_cmd(HBA_PORT *port)
{
	while (port->cmd & HBA_PxCMD_CR)
		;

	port->cmd |= HBA_PxCMD_FRE;
	port->cmd |= HBA_PxCMD_ST;
}

void stop_cmd(HBA_PORT *port)
{
	port->cmd &= ~HBA_PxCMD_ST;
	port->cmd &= ~HBA_PxCMD_FRE;

	while (1)
	{
		if (port->cmd & HBA_PxCMD_FR)
			continue;
		if (port->cmd & HBA_PxCMD_CR)
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

bool write(HBA_PORT *port, uint64_t startl, uint64_t starth, uint64_t count, char *buf)
{
	port->is = (uint64_t)0xffff;
	int slot = find_cmdslot(port);
	if (slot == -1)
		return 0;

	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER *)port->clb;
	cmdheader += slot;
	cmdheader->cfl = sizeof(FIS_REG_H2D) / sizeof(uint64_t);
	cmdheader->w = 1;
	cmdheader->c = 1;
	cmdheader->p = 1;
	cmdheader->prdtl = (uint16_t)((count - 1) >> 4) + 1;

	HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL *)(cmdheader->ctba);
	int i;
	for (i = 0; i < cmdheader->prdtl - 1; i++)
	{
		cmdtbl->prdt_entry[i].dba = (uint64_t)buf;
		cmdtbl->prdt_entry[i].dbau = (uint64_t)buf >> 32;
		cmdtbl->prdt_entry[i].dbc = 8 * 1024;
		cmdtbl->prdt_entry[i].i = 1;
		buf += 4 * 1024;
		count -= 16;
	}

	cmdtbl->prdt_entry[i].dba = (uint64_t)buf;
	cmdtbl->prdt_entry[i].dbau = (uint64_t)buf >> 32;
	cmdtbl->prdt_entry[i].dbc = count << 9;
	cmdtbl->prdt_entry[i].i = 1;

	FIS_REG_H2D *cmdfis = (FIS_REG_H2D *)(&cmdtbl->cfis);
	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->c = 1;
	cmdfis->command = 0x35;

	cmdfis->lba0 = (uint64_t)startl;
	cmdfis->lba1 = (uint64_t)(startl >> 8);
	cmdfis->lba2 = (uint64_t)(startl >> 16);
	cmdfis->device = 1 << 6;

	cmdfis->lba3 = (uint64_t)(startl >> 24);
	cmdfis->lba4 = (uint64_t)starth;
	cmdfis->lba5 = (uint64_t)(starth >> 8);

	cmdfis->countl = count & 0xff;
	cmdfis->counth = count >> 8;

	port->ci = 1;
	while (1)
	{
		if ((port->ci & (1 << slot)) == 0)
			break;
		if (port->is & (1 << 30))
		{
			println("[SATA] Error writing to Disk");
			return 0;
		}
	}
	if (port->is & (1 << 30))
	{
		println("[SATA] Error writing to Disk");
		return 0;
	}
	return 1;
}

bool read(HBA_PORT *port, uint64_t startl, uint64_t starth, uint64_t count, char *buf)
{
	port->is = (uint64_t)-1;
	int spin = 0;
	int slot = find_cmdslot(port);
	if (slot == -1)
		return 0;

	HBA_CMD_HEADER *cmdheader = (HBA_CMD_HEADER *)(port->clb);
	cmdheader += slot;
	cmdheader->cfl = sizeof(FIS_REG_H2D) / sizeof(uint64_t);
	cmdheader->w = 0;
	cmdheader->prdtl = (uint16_t)((count - 1) >> 4) + 1;

	HBA_CMD_TBL *cmdtbl = (HBA_CMD_TBL *)(cmdheader->ctba);

	int i;
	for (i = 0; i < cmdheader->prdtl - 1; i++)
	{
		cmdtbl->prdt_entry[i].dba = (uint64_t)buf;
		cmdtbl->prdt_entry[i].dbau = (uint64_t)buf >> 32;
		cmdtbl->prdt_entry[i].dbc = 8 * 1024;
		cmdtbl->prdt_entry[i].i = 1;
		buf += 4 * 1024;
		count -= 16;
	}

	cmdtbl->prdt_entry[i].dba = (uint64_t)buf;
	cmdtbl->prdt_entry[i].dbau = (uint64_t)buf >> 32;
	cmdtbl->prdt_entry[i].dbc = count << 9;
	cmdtbl->prdt_entry[i].i = 1;

	FIS_REG_H2D *cmdfis = (FIS_REG_H2D *)(&cmdtbl->cfis);

	cmdfis->fis_type = FIS_TYPE_REG_H2D;
	cmdfis->c = 1;
	cmdfis->command = 0x25;

	cmdfis->lba0 = (uint64_t)startl;
	cmdfis->lba1 = (uint64_t)(startl >> 8);
	cmdfis->lba2 = (uint64_t)(startl >> 16);
	cmdfis->device = 1 << 6;

	cmdfis->lba3 = (uint64_t)(startl >> 24);
	cmdfis->lba4 = (uint64_t)starth;
	cmdfis->lba5 = (uint64_t)(starth >> 8);

	cmdfis->countl = (count & 0xff);
	cmdfis->counth = (count >> 8);

	while ((port->tfd & (ATA_DEV_BUSY | ATA_DEV_DRQ)) && spin < 1000000)
	{
		spin++;
	}
	if (spin == 1000000)
	{
		println("[SATA] Port is idle");
		return 0;
	}

	port->ci = (1 << slot);

	while (true)
	{
		if ((port->ci & (1 << slot)) == 0)
			break;
		if (port->is & (1 << 30))
		{
			println("[SATA] Error writing to Disk");
			return 0;
		}
	}

	if (port->is & (1 << 30))
	{
		println("[SATA] Error writing to Disk");
		return 0;
	}

	return 1;
}

static const AHCI_Device_Info AHCI_IntelDevices[] = {
	{0x2922, "ICH9 (AHCI mode)"},
	{0x2923, "ICH9 (AHCI mode)"},
	{0x2924, "ICH9"},
	{0x2925, "ICH9"},
	{0x2927, "ICH9"},
	{0x2829, "Intel ICH8M (AHCI mode)"},
	{},
};

static const AHCI_Vendor_Info AHCI_KnownVendors[] = {
	{0x8086, "Intel", (AHCI_Device_Info *)AHCI_IntelDevices},
	{},
};

uint16_t pci_read_word16(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
	uint32_t address = (bus << 16) | ((slot) << 11) | ((func) << 8) |
					   (offset & 0xFC) | 0x80000000;
	outl(0xCF8, address);
	io_wait();
	volatile uint16_t tmp = ((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
	return (tmp);
}

int find_ahci_pci(uint8_t *bus, uint8_t *slot, const char **vendor_name,
				  const char **device_name)
{
	uint16_t vendor, device;
	for (int _bus = 0; _bus < 256; _bus++)
	{
		for (int _slot = 0; _slot < 32; _slot++)
		{
			vendor = pci_read_word16(_bus, _slot, 0, (0x00 | 0x0));
			for (AHCI_Vendor_Info *v = (AHCI_Vendor_Info *)AHCI_KnownVendors;
				 v->vendor; v++)
			{
				if (v->vendor == vendor)
				{
					device = pci_read_word16(_bus, _slot, 0, (0x00 | 0x02));
					for (AHCI_Device_Info *d = v->devices; d->device; d++)
					{
						if (d->device == device)
						{
							*bus = _bus;
							*slot = _slot;
							*vendor_name = v->vendor_name;
							*device_name = d->device_name;
							return 0;
						}
					}
				}
			}
		}
	}
	return 1;
}

void probe_port(HBA_MEM *abar)
{
	glob_abar = abar;

	uint32_t pi = abar->pi;
	int i = 0;

	while (i < 32)
	{
		if (pi & 1)
		{
			int dt = check_type(&abar->ports[i]);
			if (dt == AHCI_DEV_SATA)
				println("[AHCI] Device found");
		}
		pi >>= 1;
		i++;
	}
}