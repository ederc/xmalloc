/**
 * @file   page.c
 * @Author Christian Eder ( ederc@mathematik.uni-kl.de )
 * @date   July 2012
 * @brief  General source file for non-inline page handling functions.
 *         This file is part of XMALLOC, licensed under the GNU General
 *         Public License version 3. See COPYING for more information.
 */

#include "src/page.h"

/* zero page for initializing static bins */
struct xPageStruct __XMALLOC_ZERO_PAGE[] = {{0, NULL, NULL, NULL, NULL}};

unsigned long xMinPageIndex = ULLONG_MAX;
unsigned long xMaxPageIndex = 0;
unsigned long *xPageShifts = NULL;


/**********************************************
 * PAGE (UN-)REGISTRATION
 *********************************************/
void xPageIndexFault(unsigned long startIndex, unsigned long endIndex) {
  unsigned long indexDiff = endIndex - startIndex;
  long i;
  assert((startIndex <= endIndex) &&
         (endIndex > xMaxPageIndex || startIndex < xMinPageIndex));

  if (NULL == xPageShifts) {
    xPageShifts   = (unsigned long *) xAllocFromSystem((indexDiff + 1) *
                        __XMALLOC_SIZEOF_LONG);
    xMaxPageIndex = endIndex;
    xMinPageIndex = startIndex;
    for (i = 0; i <= indexDiff; i++)
      xPageShifts[i]  = 0;
  } else {
    unsigned long oldLength = xMaxPageIndex - xMinPageIndex + 1;
    unsigned long newLength = (startIndex < xMinPageIndex ?
                               (xMaxPageIndex - startIndex) :
                               (endIndex - xMinPageIndex))
                              + 1;
    xPageShifts = (unsigned long *) xReallocSizeFromSystem(xPageShifts, // TOODOO
                                        oldLength * __XMALLOC_SIZEOF_LONG,
                                        newLength * __XMALLOC_SIZEOF_LONG);

    if (startIndex < xMinPageIndex) {
      unsigned long offset  = newLength - oldLength;
      for (i = oldLength - 1; i >= 0; i--)
        xPageShifts[i + offset] = xPageShifts[i];
      for (i = 0; i < offset; i++)
        xPageShifts[i]  = 0;
      xMinPageIndex = startIndex;
    } else {
      for (i = oldLength; i < newLength; i++)
        xPageShifts[i]  = 0;
      xMaxPageIndex = endIndex;
    }
  }
}

void xRegisterPagesInRegion(void *startAddr, int numberPages) {
  char *endAddr = (char*) startAddr +
                    (numberPages - 1) * __XMALLOC_SIZEOF_SYSTEM_PAGE;

  unsigned long startIndex  = xGetPageIndexOfAddr(startAddr);
  unsigned long endIndex    = xGetPageIndexOfAddr(endAddr);
  unsigned long shift;

  // check indices & correct them if necessary
  if (startIndex < xMinPageIndex || endIndex > xMaxPageIndex)
    xPageIndexFault(startIndex, endIndex); // TOODOO

  shift = xGetPageShiftOfAddr(startAddr);
  if (startIndex < endIndex) {
    if (0 == shift)
      xPageShifts[startIndex - xMinPageIndex]  = ULLONG_MAX;
    else
      xPageShifts[startIndex - xMinPageIndex]  |= ~((((unsigned long) 1) << shift) - 1);
    for (shift = startIndex + 1; shift < endIndex; shift++)
      xPageShifts[startIndex - xMinPageIndex]  = ULLONG_MAX;
    shift = xGetPageShiftOfAddr(endAddr);
    if ((__XMALLOC_BIT_SIZEOF_LONG - 1) == shift)
      xPageShifts[endIndex - xMinPageIndex]  = ULLONG_MAX;
    else
      xPageShifts[endIndex - xMinPageIndex]  |=
        ((((unsigned long) 1) << (shift + 1)) - 1);
  } else {
    endIndex  = xGetPageShiftOfAddr(endAddr);
    while (endIndex > shift) {
      xPageShifts[startIndex - xMinPageIndex] |=
        (((unsigned long) 1) << endIndex);
      endIndex--;
    }
    xPageShifts[startIndex - xMinPageIndex] |= (((unsigned long) 1) << shift);
  }
}

void xUnregisterPagesFromRegion(void *startAddr, int numberPages) {
  unsigned long startIndex  = xGetPageIndexOfAddr(startAddr);
  char *endAddr             = (char *)startAddr +
                              (numberPages-1) * __XMALLOC_SIZEOF_SYSTEM_PAGE;
  unsigned long endIndex    = xGetPageIndexOfAddr(endAddr);
  unsigned long shift       = xGetPageShiftOfAddr(startAddr);

  if (startIndex < endIndex) {
    if (0 == shift)
      xPageShifts[startIndex - xMinPageIndex] =   0;
    else
      xPageShifts[startIndex - xMinPageIndex] &=  ((((unsigned long) 1) << shift) - 1);

    for (shift = startIndex + 1; shift < endIndex; shift++)
      xPageShifts[shift - xMinPageIndex] = 0;

    shift = xGetPageShiftOfAddr(endAddr);
    if ((__XMALLOC_BIT_SIZEOF_LONG - 1) == shift)
      xPageShifts[endIndex - xMinPageIndex] =   0;
    else
      xPageShifts[endIndex - xMinPageIndex] &=
          ~((((unsigned long) 1) << (shift + 1)) - 1);
  } else {
    // startIndex < endIndex
    endIndex  = xGetPageShiftOfAddr(endAddr);
    while (shift < endIndex) {
      xPageShifts[startIndex - xMinPageIndex] &= ~(((unsigned long) 1) << endIndex);
      endIndex--;
    }
    xPageShifts[startIndex - xMinPageIndex] &=  ~(((unsigned long) 1) << shift);
  }
}
