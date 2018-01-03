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
#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>

#include "pathnames.h"
#include "nls.h"
#include "optutils.h"

/* basic table settings */
enum {
    LSBLK_TREE = (1 << 4),
};

struct lsblk {
    
    int sort_id;

    int flags;

    // 输出所有设备, 包括空设备
    unsigned int all_devices:1; /* print all devices, including empty */

};

// 全局句柄, 目前还不知道做什么用的
static struct lsblk *lsblk; /* global handler */
//static int columns[ARRAY_SIZE(infos) * 2];
static size_t ncolumns;

struct blkdev_ctx {
    struct blkdev_ctx *parent;
};

// 初始化Debug信息, 具体功能不确定, 先留个空
static void lsblk_init_debug(void)
{

    // 是否是分区 TRUE/FALSE
    int partation;		/* is partition? TRUE/FALSE */
}

// 核心功能函数, 迭代快设备
/* Iterate devices in sysfs */
static int iterate_block_devices(void)
{
    // 系统类型
    DIR *dir;
    struct dirent *d;
    // 自定义类型
    struct blkdev_ctx ctx = { NULL };

    // 打开/sys/block目录
    if (!(dir = opendir(_PATH_SYS_BLOCK))) {
        return -errno;
    }
}

static void check_sysdevblock(void)
{

}

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
   
    // 这段代码貌似对主要功能没有影响, 先注释掉 
    // 地域设置, 第二个参数为""代表设置成当前系统的区域
    /*setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
    atexit(close_stdout);*/

    lsblk = &_ls;

    lsblk_init_debug();
    
    // 下面就是根据输入参数设置变量
    // getopt_long定义在getopt.h中
    while((c = getopt_long(argc, argv, 
            "abdDze:fhJlnmo:OpPiI:rstVSTx:", longopts, NULL)) != -1) {
        switch(c) {
        case 'a':
            lsblk->all_devices = 1;
            break;


        }
    }

    if (force_tree)
        lsblk->flags |= LSBLK_TREE;
    
    // 检查/sys/dev/block目录是否可读
    check_sysdevblock();

    // 如果列没有设置, 设置默认的列
    if (!ncolumns) {

    }
}

