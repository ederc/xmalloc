/**
 * @file   xRegion.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   August 2012
 * @brief  Region handlers for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_REGION_H
#define XMALLOC_REGION_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include "include/xmalloc-config.h"
#include "src/data.h"
#include "src/globals.h"
#include "src/bin.h"
#include "src/align.h"

/**
 * @fn xRegion xAllocNewRegion(int minNumberPages)
 *
 * @brief Allocates a new region with at least @var minNumberPages pages.
 *
 * @param minNumberPages @var int giving the minimal number of pages the newly
 * allocated region should consist of
 *
 * @return new @var xRegion
 *
 */
xRegion xAllocNewRegion(int minNumberPages);

/**
 * @fn static inline void xTakeOutRegion(xRegion region)
 *
 * @brief Removes a region from the list of regions.
 *
 * @param region @var xRegion removed from the list of regions
 *
 */
static inline void xTakeOutRegion(xRegion region) {
  if (NULL != region->prev)
    region->prev->next  = region->next;

  if (NULL != region->next)
    region->next->prev  = region->prev;
}

/**
 * @fn static inline void xInsertRegionBefore(xRegion insert, xRegion before)
 *
 * @brief Inserts a region before another one.
 *
 * @param insert @var xRegion to be inserted
 *
 * @param before @var xRegion before which a new region has to be inserted
 *
 */
static inline void xInsertRegionBefore(xRegion insert, xRegion before) {
  insert->prev  = before->prev;
  insert->next  = before;
  before->prev  = insert;
  
  if (NULL != insert->prev)
    insert->prev->next  = insert;
}

/**
 * @fn static inline void xInsertRegionAfter(xRegion insert, xRegion after)
 *
 * @brief Inserts a region after another one.
 *
 * @param insert @var xRegion to be inserted
 *
 * @param after @var xRegion after which a new region has to be inserted
 *
 */
static inline void xInsertRegionAfter(xRegion insert, xRegion after) {
  insert->next  = after->next;
  insert->prev  = after;
  after->next   = insert;

  if (NULL != insert->next)
    insert->next->prev  = insert;
}

/**
 * @fn xPage xGetConsecutivePagesFromRegion(xRegion region, int numberNeeded)
 *
 * @brief Gets a consecutive memory chunk of @var numberNeeded @var
 * xPages out of @var region.
 *
 * @param region is the region the pages are allocated from.
 *
 * @param numberNeeded is the number of pages to be allocated.
 *
 * @return first page of the consecutive bunch of @var numberNeeded @var xPages
 */
xPage xGetConsecutivePagesFromRegion(xRegion region, int numberNeeded);
#endif
