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

    char *sb_buf;
    read(port[port_num], 1024, 0, 1, sb_buf);

    ext4_superblock *superblock = (ext4_superblock*)&sb_buf;

    inodes = (ext4_inode *)malloc(superblock->total_inodes * sizeof(ext4_inode));
    bgdts = (ext4_bgdt *)malloc((int)((int)superblock->blocks_per_group / (int)(1024 << superblock->block_size)) * sizeof(ext4_bgdt));
    
    int i;
    for (i = 0; i < (int)((int)superblock->blocks_per_group / (int)(1024 << superblock->block_size)); i++)
    {
        char* bgdt_buf;
        read(port[port_num], (uint32_t)((int)((int)superblock->blocks_per_group / (int)(1024 << superblock->block_size)) * i), 0, 1, bgdt_buf);

        ext4_bgdt *bgdt = (ext4_superblock*)&bgdt_buf;
        bgdts[i] = bgdt;
    }

    for (i = 1; i < (int)superblock->total_inodes; i++)
    {
        int group_loc = i / (int)superblock->total_inodes;
        int inode_index = i % (int)superblock->total_inodes;
        int containing_block = (inode_index * superblock->total_inodes) / (int)(1024 << superblock->block_size);

        char* inode_buf;
        read(port[port_num], (uint32_t)((int)(containing_block * (int)(1024 << superblock->block_size))), 0, 1, inode_buf);

        println_int((int)bgdts[group_loc]->inode_table_start_addr);
    }
}