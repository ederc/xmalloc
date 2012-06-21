/* Copyright 2012 Hans Schoenemann
 * 
 * This file is part of XMALLOC, licensed under the GNU General Public
 * License version 3. See COPYING for more information.
 */

#include <xmalloc-config.h>

#include <stdio.h>
#include <xmalloc.h>

#define X_MAX_SMALL_BLOCK 1012

int main()
{
  int i;
  for (i=1;i<X_MAX_SMALL_BLOCK;i++)
  { 
    printf("%d \n",i);
    void *p=xmalloc(i);
    xfree(p);
  }
  return 0;
}
