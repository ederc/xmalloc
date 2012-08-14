/**
 * @file   xSystem.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   August 2012
 * @brief  System allocation calls for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef X_SYSTEM_H
#define X_SYSTEM_H

#include <stdlib.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include <xmalloc-config.h>

/*
 * @fn void* xAllocFromSystem(size_t size)
 *
 * @brief Allocates memory chunk of size \var size from the system.
 *
 * @param size size of the memory chunk
 *
 */
void* xAllocFromSystem(size_t size);

/*
 * @fn void* xVallocFromSystem(size_t size)
 *
 * @brief Allocates memory chunk of size \var size from the system. This memory
 * is pre-aligned to the page boundary.
 *
 * @param size size of the memory chunk
 *
 */
void* xVallocFromSystem(size_t size);
#endif
