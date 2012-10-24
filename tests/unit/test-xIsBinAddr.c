/**
 * \file   test-xIsBinAddr.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test testing if an addr is a bin address or not.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  int i;
  // alloc small memory blocks
  for (i = 1; i <= __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++) {
    void *p = xMalloc(i);
    __XMALLOC_ASSERT(xIsBinAddr(p) == TRUE);
    xFree(p);
  }
  // alloc big memory blocks
  while (i <= 10 * __XMALLOC_MAX_SMALL_BLOCK_SIZE) {
    void *p = xMalloc(i);
    __XMALLOC_ASSERT(xIsBinAddr(p) == FALSE);
    xFree(p);
    i++;
  }
  return 0;
}
