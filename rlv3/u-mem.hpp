/* File: z-virt.h */

/*
* Copyright (c) 1997 Ben Harrison
*
* This software may be copied and distributed for educational, research,
* and not for profit purposes provided that this copyright and statement
* are included in all such copies.
*/

#ifndef INCLUDED_Z_VIRT_H
#define INCLUDED_Z_VIRT_H

#include <cstdlib>

/* Replacements for malloc() and friends that die on failure. */
void *mem_alloc(size_t len);
void *mem_zalloc(size_t len);
void mem_free(void *p);
void *mem_realloc(void *p, size_t len);
char* rl_strdup(char* str);
char* rl_strndup(char* str, size_t len);

enum {
	MEM_POISON_ALLOC = 0x00000001,
	MEM_POISON_FREE = 0x00000002
};

extern unsigned int mem_flags;

#endif /* INCLUDED_Z_VIRT_H */