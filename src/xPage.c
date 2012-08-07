/**
 * @file   xPage.c 
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  General source file for non-inline page handling functions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <xPage.h>

void xAllocFromFullPage(void *addr, xBin bin) {
  if(bin->currentPage != xZeroPage) {
    bin->currentPage->numberUsedBlocks  = 0;
  }
  xPage newPage     = xAllocNewPageForBin(bin);
  xInsertPageToBin(bin, newPage);
  bin->currentPage  = newPage; 
  xAllocFromNonEmptyPage(addr, newpage);
}
