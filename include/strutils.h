#ifndef UTIL_LINUX_STRUTILS
#define UTIL_LINUX_STRUTILS

extern int string_to_idarray(const char *list, int ary[], size_t arysz,
        int (name2id)(const char *, size_t));
extern int string_add_to_idarray(const char *list, int ary[], size_t arysz, 
        size_t *ary_pos, int (name2id)(const char *, size_t));

#endif /* UTIL_LINUX_STRUTILS */

