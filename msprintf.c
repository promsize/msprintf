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

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef IN_MSPRINTF
#define IN_MSPRINTF
#endif

#include "msprintf.h"

FUN_FORMAT(printf, 3, 0)
int vasnprintf(char **out, size_t lim, const char *fmt, va_list a) {
  int len, chk;
  char *str;
  va_list x;
  // clamp limit
  if(lim > INT_MAX) {
    lim = INT_MAX;
  }
  // determine length
  va_copy(x, a);
  len = vsnprintf(NULL, 0, fmt, x);
  va_end(x);
  // check for errors
  assert(len >= 0);
  // clamp len to limit
  if(len > (int)lim) {
    len = lim;
  }
  // allocate
  str = malloc(len + 1);
  assert(str);
  // format
  chk = vsnprintf(str, len + 1, fmt, a);
  // check for errors
  assert(chk >= 0);
  // done
  *out = str;
  return len;
}

FUN_FORMAT(printf, 3, 4)
int asnprintf(char **out, size_t limit, const char *fmt, ...) {
  size_t res;
  va_list a;
  va_start(a, fmt);
  res = vasnprintf(out, limit, fmt, a);
  va_end(a);
  return res;
}

#ifdef MISSING_ASPRINTF

FUN_FORMAT(printf, 2, 0)
int vasprintf(char **out, const char *fmt, va_list a) {
  return vasnprintf(out, INT_MAX, fmt, a);
}

FUN_FORMAT(printf, 2, 3)
int asprintf(char **out, const char *fmt, ...) {
  size_t res;
  va_list a;
  va_start(a, fmt);
  res = vasnprintf(out, INT_MAX, fmt, a);
  va_end(a);
  return res;
}

#endif


FUN_FORMAT(printf, 2, 0)
ARG_FORMAT(2)
char *vmsnprintf(size_t limit, const char *fmt, va_list a) {
  int res;
  char *ret;
  res = vasnprintf(&ret, limit, fmt, a);
  assert(res >= 0);
  return ret;
}

FUN_FORMAT(printf, 2, 3)
ARG_FORMAT(2)
char *msnprintf(size_t limit, const char *fmt, ...) {
  char *ret = NULL;
  int res;
  va_list a;
  va_start(a, fmt);
  res = vasnprintf(&ret, limit, fmt, a);
  va_end(a);
  return ret;
}

FUN_FORMAT(printf, 1, 0)
ARG_FORMAT(1)
char *vmsprintf(const char *fmt, va_list a) {
  char *ret = NULL;
  int res;
  res = vasnprintf(&ret, INT_MAX, fmt, a);
  return ret;
}

FUN_FORMAT(printf, 1, 2)
ARG_FORMAT(1)
char *msprintf(const char *fmt, ...) {
  char *ret = NULL;
  int res;
  va_list a;
  va_start(a, fmt);
  res = vasnprintf(&ret, INT_MAX, fmt, a);
  va_end(a);
  return ret;
}
