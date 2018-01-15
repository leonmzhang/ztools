/*
 * Copyright (C) 2008 Karel Zak <kzak@redhat.com>
 * Copyright (C) 1999-2008 by Theodore Ts'o
 * 
 * This file may be redistributed under the terms of the
 * GNU Lesser General Public License.
 * 
 * (based on list.h from e2fsprogs)
 * Merge sort based on kernel's implementation.
 */

#ifndef UTIL_LINUX_LIST_H
#define UTIL_LINUX_LIST_H

/* TODO: use AC_C_INLINE */
#ifdef __GNUC__
#define _INLINE_ static __inline__
#else                         /* For Watcom C */
#define _INLINE_ static inline
#endif

/*
 * Simple doubly linked list implementation.
 * 
 * Some of the internal functions ("__xxx") are useful when
 * manipulating whole lists rather than single entries, as
 * sometimes we already know the next/prev entries and we can
 * generate better code by using them directly rather than
 * using the generic single-entry routines.
 */

struct list_head {
	struct list_head *next, *prev;
};

#define UTIL_LINUX_LIST_H

