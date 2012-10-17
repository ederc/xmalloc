/**
 * \file   test-xAddressIsAligned.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test of address alignments in xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  
  int i;
  void *p;
  for (i = 0; i <= __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++) {
    p = xmalloc(i);
    __XMALLOC_ASSERT(TRUE == xAddressIsAligned(p));
    xfree(p);
  }

  p = xMalloc(2048);
  // should be aligned, too
  __XMALLOC_ASSERT(TRUE == xAddressIsAligned(p));
  // since p is aligned, (char *)p-2 cannot be
  __XMALLOC_ASSERT(TRUE != xAddressIsAligned((char *)p-2));

  return 0;
}
