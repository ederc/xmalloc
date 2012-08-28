/**
 * @file   xSystem.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   August 2012
 * @brief  System allocation calls for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_SYSTEM_H
#define XMALLOC_SYSTEM_H

#include <stdlib.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include "include/xmalloc-config.h"
#include "src/align.h"

/*
 * @fn void* xAllocFromSystem(size_t size)
 *
 * @brief Allocates memory chunk of size @var size from the system.
 *
 * @param size size of the memory chunk
 *
 * @return address of allocated memory
 *
 */
void* xAllocFromSystem(size_t size);

/*
 * @fn void* xVallocFromSystem(size_t size)
 *
 * @brief Allocates memory chunk of size @var size from the system. This memory
 * is pre-aligned to the page boundary.
 *
 * @param size size of the memory chunk
 *
 * @return address of allocated memory
 *
 */
void* xVallocFromSystem(size_t size);
#endif
