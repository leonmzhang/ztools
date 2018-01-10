/*
 * Copyright (C) 2010 Davidlohr Bueso <dave@gnu.org>
 *
 * This file may be redistributed under the terms of the
 * GNU Lesser General Public License.
 *
 * General memory allocation wrappers for malloc, realloc, calloc and strdup
 */

#ifndef UTIL_LINUX_XALLOC_H
#define UTIL_LINUX_XALLOC_H

#include <stdlib.h>
#include <string.h>

#include "c.h"

#ifndef XALLOC_EXIT_CODE
# define XALLOC_EXIT_CODE EXIT_FAILURE
#endif

static inline char * __attribute__((warn_unused_result)) xstrdup(const char *str)
{
    char *ret;
    
    if (!str)
        return NULL;

    ret = strdup(str);

    if (!ret)
        err(XALLOC_EXIT_CODE, "cannot duplicate string");
    return ret;
}

#endif /* UTIL_LINUX_XALLOC_H */

