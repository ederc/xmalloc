/**
 * \file   test-size-alignments.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test of size alignments in xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  
  // 0 should stay
  size_t aligned  = xAlignSize(0);
  __XMALLOC_ASSERT(aligned == 0);

  int i;
  for (i = 1; i <= __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++) {
    aligned  = xAlignSize(i);
    // aligned should be a multiple of __XMALLOC_SIZEOF_STRICT_ALIGNMENT
    __XMALLOC_ASSERT(0 == aligned % __XMALLOC_SIZEOF_STRICT_ALIGNMENT);
  }

  return 0;
}
