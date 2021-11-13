/*
 * msprintf - Allocating variants of sprintf
 *
 * Copyright (C) 2020-2021 Ingo Albrecht <copyright@promovicz.org>
 */

#ifndef MSPRINTF_H
#define MSPRINTF_H

#include <stdarg.h>

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

/* versions with A that take a destination pointer */
FUN_FORMAT(printf, 3, 0)
extern size_t vasnprintf(char **out, size_t limit, const char *fmt, va_list a);
FUN_FORMAT(printf, 2, 0)
extern size_t vasprintf(char **out, const char *fmt, va_list a);
FUN_FORMAT(printf, 3, 4)
extern size_t asnprintf(char **out, size_t limit, const char *fmt, ...);
FUN_FORMAT(printf, 2, 3)
extern size_t asprintf(char **out, const char *fmt, ...);

/* versions with M that return the allocated string */
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
