/**
 * \file   cache.h
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Cache optimization routines.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_CACHE_H
#define XMALLOC_CACHE_H

#include <stddef.h>

/**
 * \fn size_t xCacheLineSize()
 *
 * \author Nick Strupat
 *
 * \date October 2010
 *
 * \brief Returns the cache line size in bytes.
 *
 * \return cache line size in bytes
 *
 */
size_t xCacheLineSize();
#endif
