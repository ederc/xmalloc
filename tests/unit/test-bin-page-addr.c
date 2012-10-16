/**
 * \file   test-bin-page-addr.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test page for the connection between bin, page, and address for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  int i = 1;
  void *p;
  // allocate memory and check that they lie on the very same xPage
  while (i<1009) {
    void *addr  = xMalloc(i);
    p           = xGetPageOfAddr(addr);
    __XMALLOC_ASSERT(xGetBinOfAddr(addr) == xGetBinOfPage((xPage) p));
    xFreeBinAddr(addr);
    i++;
  }
  return 0;
}
