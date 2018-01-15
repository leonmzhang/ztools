/*
 * Fundamental C definitions.
 */

#ifndef UTIL_LINUX_C_H
#define UTIL_LINUX_C_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifdef HAVE_ERR_H
# include <err.h>
#endif

#ifdef __GNUC__

/* &a[0] degrades to a pointer: a different type from an array */
/* __builtin_types_compatible_p 是gcc内部定义的内联函数*/
# define __must_be_array(a) \
    UL_BUILD_BUG_ON_ZERO(__builtin_types_compatible_p(__typeof__(a), __typeof__(&a[0])))

#else /* __GNUC__ */
#endif /* __GNUC__ */

/*
 * Force a compilation error if condition is true, but also produce a
 * result (of value 0 and type size_t), so the expression can be used
 * e.g. in a structure initializer (or wherever else comma expressions
 * aren't permitted).
 * 条件为true时会产生一个编译错误; 编译通过时可以产生一个返回值供表达式使用
 * int:n; 为struct或union中位域的定义方式
 * int:-!!(e); 使用两次非操作, 确保取值为0或-1 
 */
#define UL_BUILD_BUG_ON_ZERO(e) __extension__ (sizeof(struct { int:-!!(e); }))

/*
 * 最后加的一项"__must_be_array"如果为数组则为0, 如果不为数组, 编译出错
 */
#ifndef ARRAY_SIZE
# define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(arr))
#endif

/**
 * 该段代码主要是作为获取应用程序的名称,
 * 如调用lsblk, 得到的结果为字符串"lsblk"
 *
 */
#ifndef HAVE_PROGRAM_INVOCATION_SHORT_NAME
# ifdef HAVE___PROGNAME
extern char *__progname;
#  define program_invocation_short_name __progname
# else
#  ifdef HAVE_GETEXECNAME
#   define program_invocation_short_name \
        prog_inv_sh_nm_from_file(getexecname(), 0)
#  else
#   define program_invocation_short_name \
        prog_inv_sh_nm_from_file(__FILE__, 1)
#  endif
static char prog_inv_sh_nm_buf[256];
static inline char *
prog_inv_sh_nm_from_file(char *f, char stripext)
{
    char *t;
    
    if ((t = strrchr(f, '/')) != NULL)
        t++;
    else
        t = f;
    
    strncpy(prog_inv_sh_nm_buf, t, sizeof(prog_inv_sh_nm_buf) - 1);
    prog_inv_sh_nm_buf[sizeof(prog_inv_sh_nm_buf) - 1] = '\0';
    
    if (stripext && (t = strrchr(prog_inv_sh_nm_buf, '.')) != NULL)
        *t = '\0';
    
    return prog_inv_sh_nm_buf;
}
# endif
#endif

/*
 *  * Fallback defines for old versions of glibc
 *   */
#include <fcntl.h>

#define UTIL_LINUX_VERSION _("%s from %s\n"), program_invocation_short_name, PACKAGE_STRING

#endif /* UTIL_LINUX_C_H */

