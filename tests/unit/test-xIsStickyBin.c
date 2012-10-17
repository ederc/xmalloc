/**
 * \file   test-xIsStickyBin.c
 * \Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for sticky bins for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  // get a non-sticky bin
  xBin bin = xMalloc(sizeof(xBinType));
  __XMALLOC_ASSERT(0 == xIsStickyBin(bin));
  
  // get the corresponding sticky bin
  xBin sBin = xGetStickyBinOfBin(bin);
  __XMALLOC_ASSERT(1 == xIsStickyBin(sBin));
  
  return 0;
}
