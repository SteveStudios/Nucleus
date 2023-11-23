// ext4.c - ext4 Filesystem Driver
// Created 2023/11/12 by Stephen Byrne

#include "ext4.h"

extern pci_device **pci_devices;

ext4_inode *root_inode;
ext4_superblock *superblock;

void reload_root_inode_ext4(int port_num)
{
    struct port_data **port = probe_port((HBA_MEM *)pci_devices[port_num]);

    int root = 2;
    if (superblock->total_inodes < 2)
        root = 1;

    int group_loc = root / (int)superblock->total_inodes;
    int inode_index = root % (int)superblock->total_inodes;
    int containing_block = (inode_index * superblock->total_inodes) / (int)(1024 << superblock->block_size);

    char *bgdt_buf;
    read(port[port_num], (uint32_t)((int)(superblock->blocks_per_group / (int)(1024 << superblock->block_size))), (uint32_t)((int)(superblock->blocks_per_group / (int)(1024 << superblock->block_size))) << 32, 1, &bgdt_buf);

    ext4_bgdt *bgdt = (ext4_bgdt *)&bgdt_buf;

    char *inode_buf;
    read(port[port_num], (uint32_t)(bgdt->inode_table_start_addr), (uint32_t)(bgdt->inode_table_start_addr_32), (uint32_t)superblock->inode_byte_size, &inode_buf);

    root_inode = (ext4_inode *)&inode_buf;
}

void read_file_ext4(char *file_name, int port_num)
{
    char *full_data;

    struct port_data **port = probe_port((HBA_MEM *)pci_devices[port_num]);
    ext4_inode_block *i_block = root_inode->block;
    
    if (i_block->direct_block_ptr_1 != 0)
    {
        char *temp_buf;
        read(port[port_num], (uint32_t)(i_block->direct_block_ptr_1 * (int)(1024 << superblock->block_size)), (uint32_t)((i_block->direct_block_ptr_1 * (int)(1024 << superblock->block_size)) << 32), (uint32_t)(1024 << superblock->block_size), &temp_buf);

        int i = 0;
        while (i < root_inode->byte_size)
        {
            ext4_dir_entry_2 *dir_ent = (void *)(temp_buf + (i % (int)(1024 << superblock->block_size)));
            println_int(dir_ent->name);

            i += dir_ent->dir_entry_len;
        }
    }
}

void init_ext4(int port_num)
{
    struct port_data **port = probe_port((HBA_MEM *)pci_devices[port_num]);

    char sb_buf;
    read(port[port_num], 1024, 1024 << 32, 2048, &sb_buf);

    superblock = (ext4_superblock *)&sb_buf;
    println_int((int)superblock->total_inodes);

    reload_root_inode_ext4(port_num);
}