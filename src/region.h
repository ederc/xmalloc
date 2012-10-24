/**
 * \file   region.h
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   August 2012
 * \brief  Region handlers for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#ifndef XMALLOC_REGION_H
#define XMALLOC_REGION_H

#include <stdlib.h>
#include <string.h>
#include <limits.h> // for ULLONG_MAX etc.
#include "xassert.h"
#include "xmalloc-config.h"
#include "data.h"
#include "globals.h"
#include "bin.h"
#include "align.h"
#include "system.h"

/**
 * \fn static inline BOOLEAN xIsRegionEmpty(xRegion region)
 *
 * \brief Tests if \c region is empty or not
 *
 * \param region \c xRegion to be checked
 *
 * \return true if \c region is empty, false else
 *
 */
static inline BOOLEAN xIsRegionEmpty(xRegion region) {
  return ((NULL == region->current) && (NULL == region->initAddr));
}

/**
 * \fn xRegion xAllocNewRegion(int minNumberPages)
 *
 * \brief Allocates a new region with at least \c minNumberPages pages.
 *
 * \param minNumberPages \c int giving the minimal number of pages the newly
 * allocated region should consist of
 *
 * \return new \c xRegion
 *
 */
xRegion xAllocNewRegion(int minNumberPages);

/**
 * \fn static inline void xTakeOutRegion(xRegion region)
 *
 * \brief Removes a region from the list of regions.
 *
 * \param region \c xRegion removed from the list of regions
 *
 */
static inline void xTakeOutRegion(xRegion region) {
  if (NULL != region->prev)
    region->prev->next  = region->next;

  if (NULL != region->next)
    region->next->prev  = region->prev;
}

/**
 * \fn static inline void xInsertRegionBefore(xRegion insert, xRegion before)
 *
 * \brief Inserts a region before another one.
 *
 * \param insert \c xRegion to be inserted
 *
 * \param before \c xRegion before which a new region has to be inserted
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
 * \fn static inline void xInsertRegionAfter(xRegion insert, xRegion after)
 *
 * \brief Inserts a region after another one.
 *
 * \param insert \c xRegion to be inserted
 *
 * \param after \c xRegion after which a new region has to be inserted
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
 * \fn xPage xGetConsecutivePagesFromRegion(xRegion region, int numberNeeded)
 *
 * \brief Gets a consecutive memory chunk of \c numberNeeded \c
 * xPages out of \c region.
 *
 * \param region is the region the pages are allocated from.
 *
 * \param numberNeeded is the number of pages to be allocated.
 *
 * \return first page of the consecutive bunch of \c numberNeeded \c xPages
 */
xPage xGetConsecutivePagesFromRegion(xRegion region, int numberNeeded);

/**
 * \fn static inline void xFreeRegion(xRegion region)
 *
 * \brief Frees \c region
 *
 * \param region to be freed.
 *
 */
static inline void xFreeRegion(xRegion region) {

#ifndef __XMALLOC_NDEBUG
  info.availablePages -=  region->totalNumberPages;
  info.currentRegionsAlloc--;
#endif
  xUnregisterPagesFromRegion(region->addr, region->totalNumberPages);
  xVfreeToSystem(region->addr, region->totalNumberPages * __XMALLOC_SIZEOF_SYSTEM_PAGE);
  xFreeSizeToSystem(region, sizeof(xRegionType));
}

/************************************************
 * FREEING OPERATIONS CONCERNING PAGES
 ***********************************************/
/**
 * \fn void xFreePagesFromRegion(xPage page, int quantity)
 *
 * \brief Frees \c quantity \c xPages from region starting at \c page .
 *
 * \param page \c xPage starting point of freeing
 *
 * \param quantity \c int number of pages to be freed
 *
 */
void xFreePagesFromRegion(xPage page, int quantity);

#endif
