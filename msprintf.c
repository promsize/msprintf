
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define IN_MSPRINTF

#include "msprintf.h"

FUN_FORMAT(printf, 3, 0)
size_t vasnprintf(char **out, size_t lim, const char *fmt, va_list a) {
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

FUN_FORMAT(printf, 2, 0)
size_t vasprintf(char **out, const char *fmt, va_list a) {
  return vasnprintf(out, INT_MAX, fmt, a);
}

FUN_FORMAT(printf, 3, 4)
size_t asnprintf(char **out, size_t limit, const char *fmt, ...) {
  size_t res;
  va_list a;
  va_start(a, fmt);
  res = vasnprintf(out, limit, fmt, a);
  va_end(a);
  return res;
}

FUN_FORMAT(printf, 2, 3)
size_t asprintf(char **out, const char *fmt, ...) {
  size_t res;
  va_list a;
  va_start(a, fmt);
  res = vasnprintf(out, INT_MAX, fmt, a);
  va_end(a);
  return res;
}


FUN_FORMAT(printf, 2, 0)
ARG_FORMAT(2)
char *vmsnprintf(size_t limit, const char *fmt, va_list a) {
  int res;
  char *ret;
  res = vasnprintf(&ret, limit, fmt, a);
  assert(res >= 0);
  return ret;
}

FUN_FORMAT(printf, 1, 0)
ARG_FORMAT(1)
char *vmsprintf(const char *fmt, va_list a) {
  int res;
  char *ret;
  res = vasnprintf(&ret, INT_MAX, fmt, a);
  assert(res >= 0);
  return ret;
}

FUN_FORMAT(printf, 2, 3)
ARG_FORMAT(2)
char *msnprintf(size_t limit, const char *fmt, ...) {
  int res;
  char *ret;
  va_list a;
  va_start(a, fmt);
  res = vasnprintf(&ret, limit, fmt, a);
  va_end(a);
  assert(res >= 0);
  return ret;
}

FUN_FORMAT(printf, 1, 2)
ARG_FORMAT(1)
char *msprintf(const char *fmt, ...) {
  int res;
  char *ret;
  va_list a;
  va_start(a, fmt);
  res = vasnprintf(&ret, INT_MAX, fmt, a);
  va_end(a);
  assert(res >= 0);
  return ret;
}
