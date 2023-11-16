// ext4.c - ext4 Filesystem Driver
// Created 2023/11/12 by Stephen Byrne

#include "ext4.h"

ext4_inode **inodes;
ext4_bgdt **bgdts;

void init_ext4_superblock(int port_num)
{
    HBA_MEM mem;
    mem.pi = 0x0C;

    struct port_data **port = probe_port(&mem);

    unsigned char sb_buf;
    read(port[port_num], 1024, 1024 << 32, 1, &sb_buf);

    ext4_superblock *superblock = (ext4_superblock *)&sb_buf;
        
    println_int((int)(superblock->total_inodes));

    inodes = (ext4_inode *)malloc((int)(superblock->total_inodes) * sizeof(ext4_inode));
    bgdts = (ext4_bgdt *)malloc((int)(superblock->blocks_per_group / (1024 << superblock->block_size)) * sizeof(ext4_bgdt));

    int i;
    for (i = 0; i < (int)(superblock->blocks_per_group / (1024 << superblock->block_size)); i++)
    {
        unsigned char bgdt_buf;
        read(port[port_num], (uint32_t)((int)(superblock->blocks_per_group / (1024 << superblock->block_size)) * i), (uint32_t)((int)(superblock->blocks_per_group / (1024 << superblock->block_size)) * i) << 32, 1, &bgdt_buf);

        ext4_bgdt *bgdt = (ext4_bgdt *)&bgdt_buf;
        bgdts[i] = bgdt;
    }

    for (i = 2; i < (int)superblock->total_inodes; i++)
    {
    }
}