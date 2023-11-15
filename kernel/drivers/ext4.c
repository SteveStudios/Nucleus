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

    ext4_superblock *superblock = (ext4_superblock*)&buf;
}