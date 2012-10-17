/**
 * \file   test-spec-bins-large-blocks.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for special bins, large memory blocks file for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  int i = __XMALLOC_MAX_SMALL_BLOCK_SIZE;
  for (i; i < 10 * __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++) {
    xBin b  = xGetSpecBin(i);
    __XMALLOC_ASSERT(NULL != b && "There must exist a bin in xStaticBin for this size class.");
    xUnGetSpecBin(&b, 0);
  }
  return 0;
}

