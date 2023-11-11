// str.c - C standard library compliant string and char function replacements
// Created 2023/7/10 by Stephen Byrne

#include "str.h"

int strlen(const char *str)
{
    const char *s;
    for (s = str; *s; ++s)
        ;

    return (s - str);
}

int strcmp(const char *p1, const char *p2)
{
    const unsigned char *s1 = (const unsigned char *)p1;
    const unsigned char *s2 = (const unsigned char *)p2;
    unsigned char c1, c2;
    do
    {
        c1 = (unsigned char)*s1++;
        c2 = (unsigned char)*s2++;
        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);
    return c1 - c2;
}
