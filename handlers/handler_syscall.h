// handler_syscall.h - System call handler
// Created 2023/11/18 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "../kernel_lib/io.h"
#include "../kernel_lib/str.h"

    void handle_syscall(int rax, void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);

#ifdef __cplusplus
}
#endif