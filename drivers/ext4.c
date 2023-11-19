// ext4.c - ext4 Filesystem Driver
// Created 2023/11/12 by Stephen Byrne

#include "ext4.h"

extern pci_device **pci_devices;

ext4_superblock *superblock;

ext4_inode **inodes;
ext4_bgdt **bgdts;

void reload_ext4(int port_num)
{
    struct port_data **port = probe_port((HBA_MEM*)pci_devices[port_num]);

    char *sb_buf;
    read(port[port_num], 1024, 1024 << 32, 1, &sb_buf);

    superblock = (ext4_superblock *)&sb_buf;
    println_int(superblock->total_inodes);

    free(bgdts);
    free(inodes);

    inodes = malloc((size_t)((superblock->total_inodes) * sizeof(ext4_inode)));
    bgdts = malloc((size_t)((superblock->blocks_per_group / (1024 << superblock->block_size)) * sizeof(ext4_bgdt)));

    int i;
    for (i = 0; i < (int)(superblock->blocks_per_group / (int)(1024 << superblock->block_size)); i++)
    {
        char *bgdt_buf;
        read(port[port_num], (uint32_t)((int)(superblock->blocks_per_group / (1024 << superblock->block_size)) * i), (uint32_t)((int)(superblock->blocks_per_group / (1024 << superblock->block_size)) * i) << 32, 1, &bgdt_buf);

        ext4_bgdt *bgdt = (ext4_bgdt *)&bgdt_buf;
        bgdts[i] = bgdt;
    }

    for (i = 2; i < (int)((int)superblock->total_inodes + 2); i++)
    {
        int group_loc = i / (int)superblock->total_inodes;
        int inode_index = i % (int)superblock->total_inodes;
        int containing_block = (inode_index * superblock->total_inodes) / (int)(1024 << superblock->block_size);

        char *inode_buf;
        read(port[port_num], (uint32_t)((int)(containing_block * (int)(1024 << superblock->block_size))), (uint32_t)((int)(containing_block * (int)(1024 << superblock->block_size))) << 32, 1, &inode_buf);

        ext4_inode *inode = (ext4_inode *)&inode_buf;
        inodes[i] = inode;
    }
}