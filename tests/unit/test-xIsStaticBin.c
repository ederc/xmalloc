/**
 * \file   test-xIsStaticBin.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test if bin is static or not.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  int i;
  // alloc small memory blocks from static bins
  for (i = 1; i < __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++) {
    void *p = xMalloc(i);
    xBin bin  = xGetBinOfAddr(p);
    __XMALLOC_ASSERT(xIsStaticBin(bin) == TRUE);
    xFree(p);
  }
  // alloc new bin, which is not from the static ones
  xBin newBin = xMalloc(sizeof(xBinType));
  __XMALLOC_ASSERT(xIsStaticBin(newBin) == FALSE);

  return 0;
}
