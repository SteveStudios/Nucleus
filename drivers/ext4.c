// ext4.c - ext4 Filesystem Driver
// Created 2023/11/12 by Stephen Byrne

#include "ext4.h"

HBA_MEM *mem_hba;

extern pci_device **pci_devices;

ext4_inode *root_inode;
ext4_superblock *superblock;

void reload_root_inode_ext4(int port_num)
{
    char *bgdt_buf = malloc(1);
    read(&(mem_hba->ports[0]), (uint64_t)((int)(superblock->blocks_per_group / (int)(1024 << superblock->block_size))), (uint64_t)((int)(superblock->blocks_per_group / (int)(1024 << superblock->block_size))) << 32, 1, bgdt_buf);

    ext4_bgdt *bgdt = (ext4_bgdt *)&bgdt_buf;

    char *inode_buf = malloc((int)superblock->inode_byte_size);
    read(&(mem_hba->ports[0]), (uint64_t)(bgdt->inode_table_start_addr), (uint64_t)(bgdt->inode_table_start_addr_32), (uint64_t)superblock->inode_byte_size, inode_buf);
    free(bgdt_buf);

    root_inode = (ext4_inode *)inode_buf;
}

void read_file_ext4(char *file_name, int port_num)
{
    ext4_inode_block *i_block = (ext4_inode_block *)(uint64_t)(root_inode->block);

    if (i_block->direct_block_ptr_1 != 0)
    {
        char *temp_buf = malloc((int)(1024 << superblock->block_size));
        read(&(mem_hba->ports[0]), (uint64_t)(i_block->direct_block_ptr_1 * (int)(1024 << superblock->block_size)), (uint64_t)(i_block->direct_block_ptr_1 * (int)(1024 << superblock->block_size)) << 32, (uint64_t)(1024 << superblock->block_size), temp_buf);

        int i = 0;
        while (i < root_inode->byte_size)
        {
            ext4_dir_entry_2 *dir_ent = (void *)(temp_buf + (i % (int)(1024 << superblock->block_size)));
            println((char *)(dir_ent->name));

            i += dir_ent->dir_entry_len;
        }
        free(temp_buf);
    }
}

void bring_down(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
    uint32_t address;
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

    asm volatile("outl %0, %1" : : "a"(address), "Nd"((uint16_t)0xCF8));
    asm volatile("outl %0, %1" : : "a"(0x30000000), "Nd"((uint16_t)0xCFC));
}

bool init_ext4(int port_num)
{
    uint8_t bus, slot;
    const char *vendor_name, *device_name;

    if (find_ahci_pci(&bus, &slot, &vendor_name, &device_name) != 0)
        return true;

    bring_down(bus, slot, 0, 0x24);

    uint64_t mem = ((uint64_t)(((uint32_t)((pci_read_word(bus, slot, 0, 0x26) & 0xFFFF) << 16)) | ((uint32_t)(pci_read_word(bus, slot, 0, 0x24) & 0xFFFF)))) & 0xFFFFFFFF;
    mem_hba = (HBA_MEM *)mem;

    probe_port(mem_hba);

    char *sb_buf = malloc(2048);
    read(&(mem_hba->ports[0]), (uint64_t)1024, (uint64_t)1024 << 32, (uint64_t)2048, sb_buf);

    superblock = (ext4_superblock *)sb_buf;
    println_int(superblock->total_blocks);

    reload_root_inode_ext4(port_num);

    return false;
}