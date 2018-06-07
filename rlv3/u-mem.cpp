/*
* File: z-virt.c
* Purpose: Memory management routines
*
* Copyright (c) 1997 Ben Harrison.
*
* This work is free software; you can redistribute it and/or modify it
* under the terms of either:
*
* a) the GNU General Public License as published by the Free Software
*    Foundation, version 2, or
*
* b) the "Angband licence":
*    This software may be copied and distributed for educational, research,
*    and not for profit purposes provided that this copyright and statement
*    are included in all such copies.  Other copyrights may also apply.
*
* Modifications:
*   Remove string_* functions
*   Change file name
*   Remove reliance on other z-* files
*
*/
#include "u-mem.h"
#include "u-util.h"
#include <cstring>
unsigned int mem_flags = 0;

#define SZ(uptr)	*((size_t *)((char *)(uptr) - sizeof(size_t)))

/*
* Allocate `len` bytes of memory.
*
* Returns:
*  - NULL if `len` == 0; or
*  - a pointer to a block of memory of at least `len` bytes
*
* Doesn't return on out of memory.
*/
void *mem_alloc(size_t len)
{
	char *mem;

	/* Allow allocation of "zero bytes" */
	if (len == 0) return (NULL);

	mem = malloc(len + sizeof(size_t));
	if (!mem)
		quit("Out of Memory!", EXIT_FAILURE);
	mem += sizeof(size_t);
	if (mem_flags & MEM_POISON_ALLOC)
		memset(mem, 0xCC, len);
	SZ(mem) = len;

	return mem;
}

void *mem_zalloc(size_t len)
{
	void *mem = mem_alloc(len);
	memset(mem, 0, len);
	return mem;
}

void mem_free(void *p)
{
	if (!p) return;

	if (mem_flags & MEM_POISON_FREE)
		memset(p, 0xCD, SZ(p));
	free((char *)p - sizeof(size_t));
}

void *mem_realloc(void *p, size_t len)
{
	char *m = p;

	/* Fail gracefully */
	if (len == 0) return (NULL);

	m = realloc(m ? m - sizeof(size_t) : NULL, len + sizeof(size_t));
	m += sizeof(size_t);

	/* Handle OOM */
	if (!m) quit("Out of Memory!", EXIT_FAILURE);
	SZ(m) = len;

	return m;
}

char* rl_strdup(char* str)
{
	size_t len = strlen(str);
	char* dest = mem_zalloc(len + 1);
	strcpy(dest, str);
	return dest;
}

char* rl_strndup(char* str, size_t len)
{
	char* dest = mem_zalloc(len + 1);
	return memcpy(dest, str, len);
}