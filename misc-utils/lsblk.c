/*
 * lsblk(8) - list block devices
 *
 * Copyright (C) 2010,2011,2012 Red Hat, Inc. All rights reserved.
 * Written by Milan Broz <mbroz@redhat.com>
 *            Karel Zak <kzak@redhat.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it would be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <locale.h>

#include "optutils.h"

/* basic table settings */
enum {
    LSBLK_TREE = (1 << 4),
};

struct lsblk {
    
    int sort_id;

    int flags;

};

int main(int argc, char *argv[])
{
    struct lsblk _ls = { .sort_id = -1, .flags = LSBLK_TREE };
    int c, status = EXIT_FAILURE;
    char *outarg = NULL;
    size_t i;
    int force_tree = 0;

    static const struct option longopts[] = {
        { "all",     no_argument, NULL, 'a' },
        { "bytes",   no_argument, NULL, 'b' }
    };
    
    static const ul_excl_t excl[] = {};
    int excl_st[ARRAY_SIZE(excl)];

    setlocale(LC_ALL, "");
}

