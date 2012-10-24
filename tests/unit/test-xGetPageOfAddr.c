/**
 * \file   test-xGetPageOfAddr.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test page for address for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  int i = 1, j = 1;
  // allocate memory and check that they lie on the very same xPage
  void *pa;
  void *pb;
  while (i<1009) {
    void *addra = xMalloc(i);
    void *addrb = xMalloc(i);
    pa  = xGetPageOfAddr(addra);
    pb  = xGetPageOfAddr(addrb);
    __XMALLOC_ASSERT(pa == pb);
    xFreeBinAddr(addra);
    xFreeBinAddr(addrb);
    i++;
  }

  // allocate 5 big blocks in memory ( 1007 bytes )
  // => the first 4 are on the same page, 
  //    the fifth has to be on a different one
  void *addr[5];
  void *p[5];
  for (i = 0; i <= 4; i++) {
    addr[i] = xMalloc(1007);
    p[i]    = xGetPageOfAddr(addr[i]);
  }
  // those should all be on the same page
  for(i = 0; i < 3; i++)
    for(j = 1; j <=3; j++)
      __XMALLOC_ASSERT(p[i] = p[j]);

  // p[4] should be on a different page
  __XMALLOC_ASSERT(p[4] != p[0]);

  return 0;
}

