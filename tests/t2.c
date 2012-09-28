/**
 * @file   t2.c
 * @Author Hans Schoenemann ( hannes@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  Test file for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main()
{
  int i;
  for (i=1;i<__XMALLOC_MAX_SMALL_BLOCK_SIZE;i++)
  {
    xBin b=xGetSpecBin(i);
    assert (NULL != b && "There must exist a bin in xStaticBin for this size class.");
    void *p=xMalloc(i);
    assert (NULL != p && "xMalloc should have allocated addr != NULL.");
    xFree(p);
  }
  return 0;
}
