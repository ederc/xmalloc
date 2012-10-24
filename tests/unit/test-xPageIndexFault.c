/**
 * \file   test-xIndexPageFault.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for xIndexPageFault for xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {

  int i;
  // xPageShifts is NULL in the beginning
  __XMALLOC_ASSERT(xPageShifts == NULL);

  xPageIndexFault(30,32);
  // now xPageShifts should have length 3 and all entries should be zero
  __XMALLOC_ASSERT(xPageShifts != NULL);
  __XMALLOC_ASSERT(xPageShifts[0] == 0);
  __XMALLOC_ASSERT(xPageShifts[1] == 0);
  __XMALLOC_ASSERT(xPageShifts[2] == 0);

  xPageIndexFault(40,44);
  // now xPageShifts should have length 15 and all entries should be zero
  for (i=0; i < 15; i++) 
    __XMALLOC_ASSERT(xPageShifts[i] == 0);

  xPageIndexFault(20,34);
  // now xPageShifts should have length 25 and all entries should be zero. there
  // has to be an offset of 10
  for (i=0; i < 25; i++) 
    __XMALLOC_ASSERT(xPageShifts[i] == 0);

  return 0;
}
