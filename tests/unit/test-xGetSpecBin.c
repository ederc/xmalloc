/**
 * \file   test-xGetSpecBin.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for special bin allocation for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {

  xBin b      = xGetSpecBin(__XMALLOC_MAX_SMALL_BLOCK_SIZE);
  __XMALLOC_ASSERT(NULL == b->lastPage);
  __XMALLOC_ASSERT(__XMALLOC_ZERO_PAGE == b->currentPage);
  __XMALLOC_ASSERT(0 == b->sticky);
  xUnGetSpecBin(&b, 0);

  return 0;
}
