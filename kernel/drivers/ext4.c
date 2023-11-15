// ext4.c - ext4 Filesystem Driver
// Created 2023/11/12 by Stephen Byrne

#include "ext4.h"

void init_ext4_superblock()
{
    HBA_MEM mem;
    mem.pi = 0x0C;

    struct port_data **port = probe_port(&mem);

    char *buf;
    read(port[0], 1024, 0, 1, buf);

    ext4_superblock superblock;
    superblock.total_inodes = buf[0] | buf[1] | buf[2] | buf[3];
    superblock.total_blocks = buf[4] | buf[5] | buf[6] | buf[7];
    superblock.reserved_blocks = buf[8] | buf[9] | buf[10] | buf[11];
    superblock.unallocated_blocks = buf[12] | buf[13] | buf[14] | buf[15];
    superblock.unallocated_inodes = buf[16] | buf[17] | buf[18] | buf[19];
    superblock.superblock_loc = buf[20] | buf[21] | buf[22] | buf[23];
    superblock.block_size = buf[24] | buf[25] | buf[26] | buf[27];
    superblock.fragment_size = buf[28] | buf[29] | buf[30] | buf[31];
    superblock.blocks_per_group = buf[32] | buf[33] | buf[34] | buf[35];
    superblock.fragments_per_group = buf[36] | buf[37] | buf[38] | buf[39];
    superblock.inodes_per_group = buf[40] | buf[41] | buf[42] | buf[43];
    superblock.posix_last_mount_time = buf[44] | buf[45] | buf[46] | buf[47];
    superblock.posix_last_write_time = buf[48] | buf[49] | buf[50] | buf[51];

    superblock.times_mounted_before_cc = buf[52] | buf[53];
    superblock.mounts_per_cc = buf[54] | buf[55];
    superblock.magic_signature = buf[56] | buf[57];
    superblock.fs_state = buf[58] | buf[59];
    superblock.do_when_err = buf[60] | buf[61];
    superblock.minor_version = buf[62] | buf[63];

    superblock.last_cc = buf[64] | buf[65] | buf[66] | buf[67];
    superblock.posix_forced_cc_interval = buf[68] | buf[69] | buf[70] | buf[71];
    superblock.os_id = buf[72] | buf[73] | buf[74] | buf[75];
    superblock.major_version = buf[76] | buf[77] | buf[78] | buf[79];

    superblock.user_id_reserved = buf[80] | buf[81];
    superblock.group_id_reserved = buf[82] | buf[83];
}