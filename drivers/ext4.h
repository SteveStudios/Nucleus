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
#include "../kernel_lib/mem.h"

    typedef struct __attribute__((packed))
    {
        unsigned int total_inodes;
        unsigned int total_blocks;
        unsigned int reserved_blocks;
        unsigned int unallocated_blocks;
        unsigned int unallocated_inodes;
        unsigned int superblock_loc;

        // IMPORTANT block_size and fragment_size need to be shifted to the left by 1024 to produce an accurate value
        // e.g: 1024 << block_size, 1024 << fragment_size
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

    typedef struct __attribute__((packed))
    {
        unsigned int block_usage_bitmap_addr;
        unsigned int inode_usage_bitmap_addr;
        unsigned int inode_table_start_addr;
        unsigned short unallocated_blocks_in_group;
        unsigned short unallocated_inodes_in_group;
        unsigned short directories_in_group;
        unsigned short present_group_features;
        unsigned int snapshot_block_addr;
        unsigned short block_usage_bitmap_checksum;
        unsigned short inode_usage_bitmap_checksum;
        unsigned short free_inodes;
        unsigned short block_group_checksum;

        // Valid if 64-bit feature is set and the superblock's group desciptor size is greater than 32
        unsigned int block_usage_bitmap_addr_32;
        unsigned int inode_usage_bitmap_addr_32;
        unsigned int inode_table_start_addr_32;
        unsigned short unallocated_blocks_in_group_16;
        unsigned short unallocated_inodes_in_group_16;
        unsigned short directories_in_group_16;
        unsigned short free_inodes_16;
        unsigned int snapshot_block_addr_32;
        unsigned short block_usage_bitmap_checksum_16;
        unsigned short inode_usage_bitmap_checksum_16;
        unsigned int reserved;
    } ext4_bgdt;

    typedef struct __attribute__((packed))
    {
        unsigned short types_permissions;
        unsigned short user_id;
        unsigned int byte_size;
        unsigned int posix_last_access_time;
        unsigned int posix_creation_time;
        unsigned int posix_mod_time;
        unsigned int posix_del_time;
        unsigned short group_id;
        unsigned short hard_links;
        unsigned int disk_sectors;
        unsigned int flags;
        unsigned int os_specific_value_1;
        unsigned int direct_block_ptr_1;
        unsigned int direct_block_ptr_2;
        unsigned int direct_block_ptr_3;
        unsigned int direct_block_ptr_4;
        unsigned int direct_block_ptr_5;
        unsigned int direct_block_ptr_6;
        unsigned int direct_block_ptr_7;
        unsigned int direct_block_ptr_8;
        unsigned int direct_block_ptr_9;
        unsigned int direct_block_ptr_10;
        unsigned int direct_block_ptr_11;
        unsigned int singly_indirect_block_ptr;
        unsigned int doubly_indirect_block_ptr;
        unsigned int triply_indirect_block_ptr;
        unsigned int gen_number;
        unsigned int extended_attribute_block;
        unsigned int file_directory_size_32;
        unsigned int fragment_block_address;
        unsigned long long os_specific_value_2;
    } ext4_inode;

    void init_ext4_superblock(int port_num);

#ifdef __cplusplus
}
#endif