/**
 * @file   t1.c
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
  for (i = 1; i < __XMALLOC_MAX_SMALL_BLOCK_SIZE; i++)
  {
    xBin b  = xGetSpecBin(i);
    assert (NULL != b &&
        "There must exist a bin in xStaticBin for this size class.");
    void *p = xMalloc(i);
    assert (NULL != p &&
        "xMalloc should have allocated addr != NULL.");
    assert ((i > (b->sizeInWords >> __XMALLOC_LOG_SIZEOF_LONG)) &&
        "xBin word size class is less than the actual word size to be allocated.");
    assert (((b->sizeInWords >> __XMALLOC_LOG_SIZEOF_LONG) != (long) xSizeOfAddr(p)) &&
        "Size of memory stored at p does not coincide with xBin word size class.");
    xFree(p);
  }
  return 0;
}
