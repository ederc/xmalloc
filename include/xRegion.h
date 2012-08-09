/**
 * @file   xRegion.h
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   August 2012
 * @brief  Region handlers for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef X_REGION_H
#define X_REGION_H

#include <stdlib.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include "include/xmalloc-config.h"
#include "include/xDataStructures.h"
#include "include/xGlobals.h"

/**
 * @fn xRegion xAllocNewRegion(int minNumberPages)
 *
 * @brief Allocates a new region with at least \var minNumberPages pages.
 *
 * @param minNumberPages \var int giving the minimal number of pages the newly
 * allocated region should consist of
 *
 */
xRegion xAllocNewRegion(int minNumberPages);

/**
 * @fn inline void xTakeOutRegion(xRegion region)
 *
 * @brief Removes a region from the list of regions.
 *
 * @param region \var xRegion removed from the list of regions
 *
 */
inline void xTakeOutRegion(xRegion region) {
  if(NULL != region->prev)
    region->prev->next  = region->next;

  if(NULL != region->next)
    region->next->prev  = region->prev;
}

/**
 * @fn inline void xInsertRegionBefore(xRegion insert, xRegion before)
 *
 * @brief Inserts a region before another one.
 *
 * @param insert \var xRegion to be inserted
 *
 * @param before \var xRegion before which a new region has to be inserted
 *
 */
inline void xInsertRegionBefore(xRegion insert, xRegion before) {
  insert->prev  = before->prev;
  insert->next  = before;
  before->prev  = insert;
  
  if(NULL != insert->prev)
    insert->prev->next  = insert;
}

/**
 * @fn inline void xInsertRegionAfter(xRegion insert, xRegion after)
 *
 * @brief Inserts a region after another one.
 *
 * @param insert \var xRegion to be inserted
 *
 * @param after \var xRegion after which a new region has to be inserted
 *
 */
inline void xInsertRegionAfter(xRegion insert, xRegion after) {
  insert->next  = after->next;
  insert->prev  = after;
  after->next   = insert;

  if(NULL != insert->next)
    insert->next->prev  = insert;
}

/**
 * @fn xPage xGetConsecutivePagesFromRegion(xRegion region, int numberNeeded)
 *
 * @brief Gets a consecutive memory chunk of \var numberNeeded \var
 * xPages out of \var region.
 *
 * @param region is the region the pages are allocated from.
 * @param numberNeeded is the number of pages to be allocated.
 *
 */
xPage xGetConsecutivePagesFromRegion(xRegion region, int numberNeeded);
#endif
