/*
 * Copyright (C) 2014 Ondrej Oprala <ooprala@redhat.com>
 * Copyright (C) 2014 Karel Zak <kzak@redhat.com>
 *
 * This file may be distributed under the terms of the
 * GNU Lesser General Public License.
 */
#ifndef UTIL_LINUX_DEBUG_H
#define UTIL_LINUX_DEBUG_H

/*
 * util-linux debug macros
 * 
 * The debug stuff is based on <name>_debug_mask that controls what outputs is
 * expected. The mask is usually initialized by <NAME>_DEBUG= env.variable
 * 
 * After successful initialization the flag <PREFIX>_DEBUG_INIT is always set
 * to the mask (this flag is required). The <PREFIX> is usually library API
 * prefix (e.g. MNT_) or program name (e.g. CFDISK_)
 * 
 * In the code is possible to use
 * 
 *      DBG(FOO, ul_debug("this is output for foo"));
 * 
 * where for the FOO has to be defined <PREFIX>_DEBUG_FOO.
 * 
 * It's possible to initialize the mask by comma delimited strings with
 * subsystem names (e.g. "LIBMOUNT_DEBUG=options,tab"). In this case is
 * necessary to define mask names array. This functionality is optional.
 * 
 * It's strongly recommended to use UL_* macros to define/declare/use
 * the debug stuff.
 * 
 * See disk-utils/cfdisk.c: cfdisk_init_debug()  for programs debug
 *  or libmount/src/init.c: mnt_init_debug()     for library debug
 */

#endif /* UTIL_LINUX_DEBUG_H */

