/**
 * \file   test-xAreAddressesOnSamePage.c
 * \author Christian Eder ( ederc@mathematik.uni-kl.de )
 * \date   October 2012
 * \brief  Unit test for xAreAddressesOnSamPage in xmalloc.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include <stdio.h>
#include "xmalloc-config.h"
#include "xmalloc.h"

int main() {
  
    // allocate memory chunks of the same size, 4 of them fit into 1 page, the
    // fifth one has to be on another page
    void *p1  = xmalloc(__XMALLOC_MAX_SMALL_BLOCK_SIZE);
    void *p2  = xmalloc(__XMALLOC_MAX_SMALL_BLOCK_SIZE);
    void *p3  = xmalloc(__XMALLOC_MAX_SMALL_BLOCK_SIZE);
    void *p4  = xmalloc(__XMALLOC_MAX_SMALL_BLOCK_SIZE);
    void *p5  = xmalloc(__XMALLOC_MAX_SMALL_BLOCK_SIZE);
    __XMALLOC_ASSERT(xAreAddressesOnSamePage(p1, p2) == TRUE);
    __XMALLOC_ASSERT(xAreAddressesOnSamePage(p1, p3) == TRUE);
    __XMALLOC_ASSERT(xAreAddressesOnSamePage(p1, p4) == TRUE);
    __XMALLOC_ASSERT(xAreAddressesOnSamePage(p1, p5) == FALSE);
    xfree(p2);
    xfree(p3);
    xfree(p4);
    xfree(p5);

    // allocating a much smaller memory chunk, this has to on a different page
    // than the ones allocated above
    void *p6  = xmalloc(16);
    __XMALLOC_ASSERT(xAreAddressesOnSamePage(p1, p6) == FALSE);
    xfree(p6);

  return 0;
}
