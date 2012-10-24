/**
 * \file   test-t4.c
 * \author Hans Schoenemann ( hannes@mathematik.uni-kl.de )
 * \date   July 2012
 * \brief  Test file for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

#define __XMALLOC_TEST_BLOCKS 200

char *B[__XMALLOC_TEST_BLOCKS];
int main()
{
  int i;
  int j;
  for( i=0;i<__XMALLOC_TEST_BLOCKS;i++)
  {
    B[i]=(char*)xMalloc0(i+1);
    for(j=0;j<i+1;j++) B[i][j]=(char)(i %256);
  }
  for( i=0;i<__XMALLOC_TEST_BLOCKS;i+=2)
  {
    xFree(B[i]); B[i]=NULL;
  }
  for( i=0;i<__XMALLOC_TEST_BLOCKS;i++)
  {
    if (B[i]==NULL)
    {
      B[i]=(char*)xMalloc0(i/100+1);
      for(j=0;j<i/100+1;j++) B[i][j]=(char)(i %256);
    }
  }
  for( i=0;i<__XMALLOC_TEST_BLOCKS;i++)
  {
    for(j=0;j<i/100+1;j++) 
      if (B[i][j]!=(char)(i %256)) printf("i=%d, j=%d, expected %d, found %d\n",i,j,B[i][j],(i %256));
  }
  xPrintInfo();
  return 0;
}
