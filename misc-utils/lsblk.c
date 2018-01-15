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

// TODO use gcc -include to add config.h
#include "config.h"

#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <dirent.h>

#include <libsmartcols.h>

#include <assert.h>

#include "c.h"
#include "pathnames.h"
#include "nls.h"
#include "xalloc.h"
#include "strutils.h"
#include "closestream.h"
#include "optutils.h"

#include "debug.h"

/* column IDs */
enum {
    COL_NAME = 0,  // 名称 如sdb sdb1等

    COL_MAJMIN,    // 如8:0 8:16等

    COL_TARGET,  

    COL_RO,        // 只读设备
    COL_RM,        // 可移除设备

    COL_SIZE,

    COL_TYPE,

};

/* basic table settings */
enum {
    LSBLK_TREE = (1 << 4),
};


enum {
    SORT_STRING	= 0,	/* default is to use scols_cell_get_data() */
    SORT_U64	= 1	/* use private pointer from scols_cell_get_userdata() */
};

/* column names */
struct colinfo {
    const char   *name;         /* header */
    /* 宽度提示, N < 1代表终端宽度的百分比 */
    double        whint;        /* width hint (N < 1 is in percent of termwidth) */
    int           flags;        /* SCOLS_FL_* */
    const char   *help;
    
    int           sort_type;    /* SORT_* */
};

/* columns descriptions */
static struct colinfo infos[] = {
    [COL_NAME]   = { "NAME",    0.25, SCOLS_FL_TREE | SCOLS_FL_NOEXTREMES, N_("device name") },

    [COL_MAJMIN] = { "MAJ:MIN", 6, 0, N_("major:minor device number"), SORT_U64 },

    [COL_TARGET] = { "MOUNTPOINT", 0.10, SCOLS_FL_TRUNC, N_("where the device is mounted") },

    [COL_RO]     = { "RO",      1, SCOLS_FL_RIGHT, N_("read-only device") },
    [COL_RM]     = { "RM",      1, SCOLS_FL_RIGHT, N_("removable device") },

    [COL_SIZE]   = { "SIZE",    5, SCOLS_FL_RIGHT, N_("size of the device"), SORT_U64 },

    [COL_TYPE]   = { "TYPE",    4, 0, N_("device type") },
};

struct lsblk {
    
    int sort_id;

    int flags;

    // 输出所有设备, 包括空设备
    unsigned int all_devices:1; /* print all devices, including empty */

};

// 全局句柄, 目前还不知道做什么用的
static struct lsblk *lsblk; /* global handler */

/* columns[] 数组指定所有当前想要输出的列. 
 * overkill矫枉过正
 * columns的大小是infos数组的两倍 
 */
/* columns[] array specifies all currently wanted output column. The columns
 * are defined by infos[] array and you can specify (on command line) each
 * column twice. That's enough, dynamically allocated array of the columns is
 * unnecessary overkill and over-engineering in this case */
static int columns[ARRAY_SIZE(infos) * 2];
static size_t ncolumns;

static inline void add_column(int id)
{
    if (ncolumns >= ARRAY_SIZE(columns))
        errx(EXIT_FAILURE, _("too many columns specified, "
            "the limit is %zu columns"), ARRAY_SIZE(columns) - 1);
    columns[ ncolumns++ ] =  id;
}

struct blkdev_cxt {
    struct blkdev_cxt *parent;

    // /sys/block 目录中设备内核名称, 如sda, sdb等
    char *name;                 /* kernel name in /sys/block */

    // 是否是分区 TRUE/FALSE
    int partation;		/* is partition? TRUE/FALSE */
};

// 初始化Debug信息, 具体功能不确定, 先留个空
static void lsblk_init_debug(void)
{

}

/**
 * readdir的封装, 去除了"."和".."目录
 */
static struct dirent *xreaddir(DIR *dp)
{
    struct dirent *d;
    
    assert(dp);
    
    while ((d = readdir(dp))) {
        if (!strcmp(d->d_name, ".") ||
            !strcmp(d->d_name, ".."))
            continue;
        
        /* blacklist here ? */
        break;
    }
    return d;
}

// 核心功能函数, 迭代快设备
/* Iterate devices in sysfs */
static int iterate_block_devices(void)
{
    // 系统类型
    DIR *dir;
    struct dirent *d;
    // 自定义类型
    struct blkdev_cxt cxt = { NULL };

    // 打开/sys/block目录
    if (!(dir = opendir(_PATH_SYS_BLOCK))) {
        return -errno;
    }

    closedir(dir);

    return 0;
}

/* 检查/sys/dev/block是否可读 */
static void check_sysdevblock(void)
{
    if (access(_PATH_SYS_DEVBLOCK, R_OK) != 0)
        err(EXIT_FAILURE, _("failed to access sysfs directory: %s"),
                _PATH_SYS_DEVBLOCK);
}

int main(int argc, char *argv[])
{
    struct lsblk _ls = { .sort_id = -1, .flags = LSBLK_TREE };
    int c, status = EXIT_FAILURE;
    char *outarg = NULL;
    size_t i;
    int force_tree = 0;

    // 设置支持的参数
    static const struct option longopts[] = {
        { "all",     no_argument, NULL, 'a' },
        { "bytes",   no_argument, NULL, 'b' }
    };
    
    static const ul_excl_t excl[] = {};
    int excl_st[ARRAY_SIZE(excl)];
   
    // 这段代码貌似对主要功能没有影响, 先注释掉 
    // 地域设置, 第二个参数为""代表设置成当前系统的区域
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
    atexit(close_stdout);

    lsblk = &_ls;

    lsblk_init_debug();
    
    // 下面就是根据输入参数设置列, 如果没有参数, 直接跳过该while循环
    // getopt_long定义在getopt.h中
    while((c = getopt_long(argc, argv, 
            "abdDze:fhJlnmo:OpPiI:rstVSTx:", longopts, NULL)) != -1) {
        switch(c) {
        case 'a':
            lsblk->all_devices = 1;
            break;

        case 'V':
            printf(UTIL_LINUX_VERSION);
            return EXIT_SUCCESS;
        }
    }

    if (force_tree)
        lsblk->flags |= LSBLK_TREE;
    
    // 检查/sys/dev/block目录是否可读
    check_sysdevblock();

    // 如果列没有设置, 设置默认的列
    if (!ncolumns) {
        // add_column 会修改ncolumns的值, 每增加一个加1
        add_column(COL_NAME);
        add_column(COL_MAJMIN);
        add_column(COL_RM);
        add_column(COL_SIZE);
        add_column(COL_RO);
        add_column(COL_TYPE);
        add_column(COL_TARGET);
    }

    // 没有参数时 outarg 为NULL, 该段语句不执行
    /*
    if (outarg && string_add_to_idarray(outarg, columns, ARRAY_SIZE(columns), 
            &ncolumns, column_name_to_id) < 0)
        return EXIT_FAILURE;
    */

    // main函数中lsblk->初始赋值为-1 如果没有传入参数, 不会改变该值
    if (lsblk->sort_id < 0)
        /* Since Linux 4.8 we have sort devices by default, because
 	 * /sys is no more sorted */
        lsblk->sort_id = COL_MAJMIN;

    /* For --inverse --list we still follow parent->child relation */
    /* 没有参数时, 该段语句不执行
    if (lsblk->inverse && !(lsblk->flags & LSBLK_TREE))
        lsblk->force_tree_order = 1;
    */

    /* 没有参数是, 该段语句不执行 */
    /*
    if (lsblk->sort_id >= 0 && column_id_to_number(lsblk->sort_id) < 0) {
        / * the sort column is not between output columns -- add as hidden * /
        add_column(lsblk->sort_id);
        lsblk->sort_hidden = 1;
    }
    */

    // 输出结果
    //scols_print_table(lsblk->table);

    return status;
}

