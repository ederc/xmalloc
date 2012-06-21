/* Copyright 2012 Christian Eder
 * 
 * This file is part of XMALLOC, licensed under the GNU General Public
 * License version 3. See COPYING for more information.
 */

#include <xmalloc.h>
// We only need malloc.h for struct mallinfo.
#ifdef HAVE_STRUCT_MALLINFO
// Malloc can be in several places on older versions of OS X.
# if defined(HAVE_MALLOC_H)
# include <malloc.h>
# elif defined(HAVE_SYS_MALLOC_H)
# include <sys/malloc.h>
# elif defined(HAVE_MALLOC_MALLOC_H)
# include <malloc/malloc.h>
# endif
#endif

void *xmalloc(size_t size)
{
  return malloc(size);
}

void xfree(void *ptr)
{
  free(ptr);
}

void *xrealloc(void *ptr, size_t size)
{
  return realloc(ptr, size);
}

void *xcalloc(size_t nelem, size_t elsize)
{
  return calloc(nelem, elsize);
}

void *xvalloc(size_t size)
{
  return valloc(size);
}
