// str.c - C standard library compliant string and char function replacements
// Created 2023/7/10 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    int strlen(const char *str);
    int strcmp(const char *s1, const char *s2);
    void strcat(char dest[], const char src[]);

#ifdef __cplusplus
}
#endif