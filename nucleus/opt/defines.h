// defines.h - Utilities for customizing nucleus.
// Created 2023/7/20 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Should the nucleus logo be displayed? 
// It is recommended to keep this defined if you are only mildly customizing the kernel, or comment it out if you are highly customizing the kernel.
#define NUCLEUS_BRANDING

// Should the kernel utilize event-like interrupts, or continuously check for these events, even if they have not occured?
// It is recommended to keep this commented out, unless the kernel is running on older hardware which does not support interrupts.
// IMPORTANT: Setting removing or commenting this out will not completely disable interrupts, as many components of nucleus require them. --
// -- It will just not use them when polling will produce the same functionality.
// AT THE MOMENT, THIS IS USELESS (nucleus only runs on 64-bit processors right now).
// #define POLLING

#ifdef __cplusplus
}
#endif