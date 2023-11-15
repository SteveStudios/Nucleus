// ext4.h - ext4 Filesystem Driver
// Created 2023/11/12 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_INT 2147483647

#include <stdint.h>
#include "sata.h"
#include "../kernel_lib/str.h"

    typedef struct
    {
        uint32_t total_inodes;
        uint32_t total_blocks;
        uint32_t reserved_blocks;
        uint32_t unallocated_blocks;
        uint32_t unallocated_inodes;
        uint32_t superblock_loc;
        uint32_t block_size;
        uint32_t fragment_size;
        uint32_t blocks_per_group;
        uint32_t fragments_per_group;
        uint32_t inodes_per_group;
        uint32_t posix_last_mount_time;
        uint32_t posix_last_write_time;
        uint32_t times_mounted_before_cc;
        uint32_t mounts_per_cc;
        uint32_t magic_signature;
        uint32_t fs_state;
        uint32_t do_when_err;
        uint32_t minor_version;
        uint32_t last_cc;
        uint32_t posix_forced_cc_interval;
        uint32_t os_id;
        uint32_t major_version;
        uint32_t user_id_reserved;
        uint32_t group_id_reserved;
        uint32_t inode_byte_size;
        uint32_t superblock_backup_block;
        uint32_t opt_features;
        uint32_t req_features;
        uint32_t readonly_features;
        uint32_t fs_uuid;
        uint32_t volume_name;
        uint32_t last_mounted_vol;
        uint32_t compression_algorithm;
        uint32_t file_preallocate_blocks;
        uint32_t dir_preallocate_blocks;
        uint32_t reserved_gdt;
        uint32_t journal_uuid;
        uint32_t journal_inode;
        uint32_t journal_dev_num;
        uint32_t inode_orphan_head;
        uint32_t htree_has_seed_32;
        uint32_t dir_hash_algorithm;
        uint32_t journal_blocks;
        uint32_t group_descriptor_size_64;
        uint32_t mount_options;
        uint32_t first_meta_block_group;
        uint32_t fs_time_created;
        uint32_t journal_inode_backup_32;
    } ext4_superblock;

    void init_ext4_superblock();

#ifdef __cplusplus
}
#endif