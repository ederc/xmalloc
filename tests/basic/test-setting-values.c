/**
 * \file   test-setting-values.c
 * \author Hans Schoenemann ( hannes@mathematik.uni-kl.de )
 * \date   July 2012
 * \brief  Test file for xmalloc allocating memory and setting values..
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

#define __XMALLOC_TEST_BLOCKS 20000
char *B[__XMALLOC_TEST_BLOCKS];

int main() {
  int i;
  int j;
  for (i = 0; i < __XMALLOC_TEST_BLOCKS; i++) {
    B[i]  = (char *)xMalloc0((i * 4) + 1);
    for (j = 0; j <= i * 4; j++)
      B[i][j] = (char)(i % 256);
  }
  for (i = 0; i < __XMALLOC_TEST_BLOCKS; i++) {
    for (j = 0; j <= i * 4; j++) 
      __XMALLOC_ASSERT((B[i][j] == (char)(i % 256)) && "wrong value in");
  }

  for (i = __XMALLOC_TEST_BLOCKS - 1; i > -1; i--) {
    xFree(B[i]);
  }
  return 0;
}
