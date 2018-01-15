/*
 *  * Copyright (C) 2011 Karel Zak <kzak@redhat.com>
 *   */
#ifndef UTIL_LINUX_SYSFS_H
#define UTIL_LINUX_SYSFS_H

/**
 * sysfs_devname_sys_to_dev:
 * @name: devname to be converted in place
 * 
 * Linux kernel linux/drivers/base/core.c: device_get_devnode()
 * defines a replacement of '!' in the /sys device name by '/' in the
 * /dev device name. This helper replaces all occurrences of '!' in
 * @name by '/' to convert from /sys to /dev.
 */
/*
 * 内核中, 对于设备名称中包含'/'的, 使用'!'做了替换, 此处将包含'!'的
 * 设备名称替换回'/'
 */
static inline void sysfs_devname_sys_to_dev(char *name)
{
    char *c;
    
    if (name)
        while ((c = strchr(name, '!')))
            c[0] = '/';
}

#endif /* UTIL_LINUX_SYSFS_H */

