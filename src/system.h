/**
 * \file   system.h
 * \Author Christian Eder ( ederc\mathematik.uni-kl.de )
 * \date   August 2012
 * \brief  System allocation calls for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_SYSTEM_H
#define XMALLOC_SYSTEM_H

#include <stdlib.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include <fcntl.h>
#include <sys/mman.h>
#include "xassert.h"
#include "xmalloc-config.h"
#include "align.h"

/*
 * \fn void* xAllocFromSystem(size_t size)
 *
 * \brief Allocates memory chunk of size \c size from the system.
 *
 * \param size size of the memory chunk
 *
 * \return address of allocated memory
 *
 */
void* xAllocFromSystem(size_t size);

/*
 * \fn void* xReallocSizeFromSystem(void *addr, size_t oldSize, size_t newSize)
 *
 * \brief Reallocates memory chunk of size \c oldSize at \c addr to a memory
 * chunk of size \c newSize at a ( possibly ) new address.
 *
 * \param addr address of memory chunk to be reallocated
 *
 * \param oldSize old size of memory chunk to be reallocated
 *
 * \param newSize new size of memory chunk after reallocation
 *
 * \return address of reallocated memory chunk
 *
 */
void* xReallocSizeFromSystem(void *addr, size_t oldSize, size_t newSize);

/*
 * \fn void* xVallocFromSystem(size_t size)
 *
 * \brief Allocates memory chunk of size \c size from the system. This memory
 * is pre-aligned to the page boundary. This is just a wrapper around \see
 * xValloc() which ensures a 2nd try of allocating memory if the 1st one fails.
 *
 * \param size size of the memory chunk
 *
 * \return address of allocated memory
 *
 */
void* xVallocFromSystem(size_t size);

/*
 * \fn void* xVallocMmap(size_t size)
 *
 * \brief Allocates memory chunk of size \c size from the system. This memory
 * is pre-aligned to the page boundary. Mmap is used.
 *
 * \param size size of the memory chunk
 *
 * \return address of allocated memory
 *
 */
void* xVallocMmap(size_t size);

/*
 * \fn void* xVallocMmap(size_t size)
 *
 * \brief Allocates memory chunk of size \c size from the system. This memory
 * is pre-aligned to the page boundary. Mmap is NOT used.
 *
 * \param size size of the memory chunk
 *
 * \return address of allocated memory
 *
 * \note xmalloc's configure decides which valloc function is used for
 * __XMALLOC_VALLOC. This decision is done on whether mmap is available or not.
 *
 */
void* xVallocNoMmap(size_t size);

/*
 * \fn void* xFreeToSystem(void *page, size_t size)
 *
 * \brief Frees memory at \c addr to system.
 *
 * \param addr address to be freed
 *
 * \param size \size_t of the memory chunk
 *
 */
void xVfreeToSystem(void *addr, size_t size);

/*
 * \fn void* xFreeToSystem(void *page, size_t size)
 *
 * \brief Frees memory at \c addr to system.
 *
 * \param page address to be freed
 *
 * \param size size of memory to be freed
 *
 */
void xFreeSizeToSystem(void *addr, size_t size);


/************************************************
 * MEMORY SETTING AND COPYING BUSINESS
 ***********************************************/
/*
 * \fn void xMemsetInWords(void *addr, int value, size_t size)
 *
 * \brief Sets memory in word size chunks.
 *
 * \param addr starting point for memory chunk to be set to value \c value .
 *
 * \param value value the memory chunk is set to
 *
 * \param length of the memory chunk, given in words
 *
 */
static inline void xMemsetInWords(void *addr, int value, size_t length) {
  long *ptr         = (long *) addr;
  unsigned long val = value;
  unsigned long len = length;
  while (len) {
    *ptr++  = val;
    len--;
  }
}

#endif
