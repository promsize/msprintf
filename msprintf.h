/*
 * msprintf - Allocating variants of sprintf
 *
 * Copyright (C) 2020-2021 Ingo Albrecht <copyright@promovicz.org>
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

#ifndef MSPRINTF_H
#define MSPRINTF_H

#include <stdarg.h>
#include <stdio.h>

/* use attributes to enable format checking */
#if defined(__GNUC__) || defined(__clang__)
#define FUN_FORMAT(arch, fmtindex, argindex)        \
  __attribute__((format(arch, fmtindex, argindex)))
#define ARG_FORMAT(...)                             \
  __attribute__((format_arg(__VA_ARGS__)))
#else
#define FUN_FORMAT(...)
#define ARG_FORMAT(...)
#endif

/* versions with A take a destination pointer */
FUN_FORMAT(printf, 3, 0)
extern int vasnprintf(char **out, size_t limit, const char *fmt, va_list a);
FUN_FORMAT(printf, 3, 4)
extern int asnprintf(char **out, size_t limit, const char *fmt, ...);
#ifndef MISSING_ASPRINTF
FUN_FORMAT(printf, 2, 0)
extern int vasprintf(char **out, const char *fmt, va_list a);
FUN_FORMAT(printf, 2, 3)
extern int asprintf(char **out, const char *fmt, ...);
#endif

/* versions with M return the allocated string */
FUN_FORMAT(printf, 2, 0)
ARG_FORMAT(2)
extern char *vmsnprintf(size_t limit, const char *fmt, va_list a);
FUN_FORMAT(printf, 1, 0)
ARG_FORMAT(1)
extern char *vmsprintf(const char *fmt, va_list a);
FUN_FORMAT(printf, 2, 3)
ARG_FORMAT(2)
extern char *msnprintf(size_t limit, const char *fmt, ...);
FUN_FORMAT(printf, 1, 2)
ARG_FORMAT(1)
extern char *msprintf(const char *fmt, ...);

/* clean up attribute macros */
#ifndef IN_MSPRINTF
#undef FUN_FORMAT
#undef ARG_FORMAT
#endif

#endif /* !MSPRINTF_H */
