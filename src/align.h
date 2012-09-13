/**
 * @file   align.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   August 2012
 * @brief  Memory alignment handlers for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_ALIGN_H
#define XMALLOC_ALIGN_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include "xmalloc-config.h"
#include "data.h"

/**
 * @fn static inline xAlignSize(size_t size)
 *
 * @brief @var size is aligned for xmalloc.
 *
 * @param size ñvar size_t aligned for xmalloc
 *
 * @return aligned size
 *
 */
static inline size_t xAlignSize(size_t size) {
  return ((((unsigned long) size) + __XMALLOC_SIZEOF_ALIGNMENT_MINUS_ONE) &
          (~__XMALLOC_SIZEOF_ALIGNMENT_MINUS_ONE));
}

#ifndef _XMALLOC_NDEBUG
/**
 * @fn static inline bool xAddressIsAligned(void *addr)
 *
 * @brief Checks if @var addr is aligned or not.
 *
 * @param addr address to be checked
 *
 * @return true if @var addr is aligned, false else
 *
 */
static inline bool xAddressIsAligned(void *addr) {
  return(0 == (((unsigned long) addr) & __XMALLOC_SIZEOF_ALIGNMENT_MINUS_ONE));
}
#endif
#endif
