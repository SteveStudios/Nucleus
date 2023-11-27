// handler_syscall.c - System call handler
// Created 2023/11/18 by Stephen Byrne

#include "handler_syscall.h"

void handle_syscall(int rax, void* arg0, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5)
{
    switch (rax) {
        case 0:
            extern char** _std_in;
            char *buf = "";
            for (int i = 0; i < (int)(uint64_t)arg2; i++)
            {
                if (i >= sizeof(_std_in))
                    break;
                strcat(buf, _std_in[i]);
            }
            arg1 = buf;
            break;
        case 1:
            print((char*)arg1);
            break;   
    }
}