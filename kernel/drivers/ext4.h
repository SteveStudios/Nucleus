// ext4.h - ext4 Filesystem Driver
// Created 2023/11/12 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "sata.h"
#include "../kernel_lib/str.h"

    typedef struct __attribute__((packed))
    {
        unsigned int total_inodes;
        unsigned int total_blocks;
        unsigned int reserved_blocks;
        unsigned int unallocated_blocks;
        unsigned int unallocated_inodes;
        unsigned int superblock_loc;
        unsigned int block_size;
        unsigned int fragment_size;
        unsigned int blocks_per_group;
        unsigned int fragments_per_group;
        unsigned int inodes_per_group;
        unsigned int posix_last_mount_time;
        unsigned int posix_last_write_time;
        unsigned short times_mounted_before_cc;
        unsigned short mounts_per_cc;
        unsigned short magic_signature;
        unsigned short fs_state;
        unsigned short do_when_err;
        unsigned short minor_version;
        unsigned int last_cc;
        unsigned int posix_forced_cc_interval;
        unsigned int os_id;
        unsigned int major_version;
        unsigned short user_id_reserved;
        unsigned short group_id_reserved;
        unsigned int first_non_reserved_inode;
        unsigned short inode_byte_size;
        unsigned short superblock_backup_block;
        unsigned int opt_features;
        unsigned int req_features;
        unsigned int readonly_features;
        uint16_t fs_uuid;
        uint16_t volume_name;
        uint64_t last_mounted_vol;
        unsigned int compression_algorithm;
        unsigned char file_preallocate_blocks;
        unsigned char dir_preallocate_blocks;
        unsigned short reserved_gdt;
        uint16_t journal_uuid;
        unsigned int journal_inode;
        unsigned int journal_dev_num;
        unsigned int inode_orphan_head;
        uint16_t htree_has_seed_32;
        unsigned char dir_hash_algorithm;
        unsigned char journal_blocks;
        unsigned short group_descriptor_size_64;
        unsigned int mount_options;
        unsigned int first_meta_block_group;
        unsigned int fs_time_created;
        uint64_t journal_inode_backup_32;
    } ext4_superblock;

    void init_ext4_superblock();

#ifdef __cplusplus
}
#endif