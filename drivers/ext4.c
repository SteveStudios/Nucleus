// ext4.c - ext4 Filesystem Driver
// Created 2023/11/12 by Stephen Byrne

#include "ext4.h"

extern pci_device **pci_devices;

ext4_inode *root_inode;
ext4_superblock *superblock;

void reload_root_inode_ext4(int port_num)
{
    struct port_data **port = probe_port((HBA_MEM *)pci_devices[port_num]);
    if (port == NULL)
        return;

    char *bgdt_buf = malloc(8164);
    read(port[0], (uint64_t)((int)(superblock->blocks_per_group / (int)(1024 << superblock->block_size))), (uint64_t)((int)(superblock->blocks_per_group / (int)(1024 << superblock->block_size))) << 32, 1, bgdt_buf);

    ext4_bgdt *bgdt = (ext4_bgdt *)&bgdt_buf;

    char *inode_buf = malloc(8164);
    read(port[0], (uint64_t)(bgdt->inode_table_start_addr), (uint64_t)(bgdt->inode_table_start_addr_32), (uint64_t)superblock->inode_byte_size, inode_buf);
    free(bgdt_buf);

    root_inode = (ext4_inode *)inode_buf;
}

void read_file_ext4(char *file_name, int port_num)
{
    struct port_data **port = probe_port((HBA_MEM *)pci_devices[port_num]);
    if (port == NULL)
        return;

    ext4_inode_block *i_block = (ext4_inode_block *)(uint64_t)(root_inode->block);
    
    if (i_block->direct_block_ptr_1 != 0)
    {
        char *temp_buf = malloc(8164);
        read(port[0], (uint64_t)(i_block->direct_block_ptr_1 * (int)(1024 << superblock->block_size)), (uint64_t)(i_block->direct_block_ptr_1 * (int)(1024 << superblock->block_size)) << 32, (uint64_t)(1024 << superblock->block_size), temp_buf);

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

bool init_ext4(int port_num)
{   
    HBA_MEM *mem = malloc(sizeof(HBA_MEM));
    mem->fpi = port_num;

    struct port_data **port = probe_port(mem);
    if (port == NULL) {
        print("[EXT4] Failed to probe port ");
        print_int(port_num);
        print("\n");
        return true;
    }

    char *sb_buf = malloc(8164);
    read(port[0], (uint64_t)1024, (uint64_t)1024 << 32, (uint64_t)2048, sb_buf);

    superblock = (ext4_superblock *)&sb_buf;
    println_int((int)superblock->total_inodes);

    reload_root_inode_ext4(port_num);

    return false;
}