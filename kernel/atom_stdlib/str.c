// str.c - C standard library compliant string and char function replacements
// Created 2023/7/10 by Stephen Byrne

#include "str.h"

int strlen(const char* str)
{
	const char *s;
	for (s = str; *s; ++s);
    
	return (s - str);
}