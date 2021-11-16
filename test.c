
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "msprintf.h"

int main(void) {
  size_t l;
  char *s;

  // asprintf

#ifdef MISSING_ASPRINTF
  l = asprintf(&s, "%c\n", 'a');
  assert(l == 2);
  assert(strcmp(s, "a\n") == 0);
  free(s);

  l = asprintf(&s, "%d\n", 123);
  assert(l == 4);
  assert(strcmp(s, "123\n") == 0);
  free(s);

  l = asprintf(&s, "%s\n", "test");
  assert(l == 5);
  assert(strcmp(s, "test\n") == 0);
  free(s);
#endif

  // asnprintf

  l = asnprintf(&s, 6, "%s\n", "test");
  assert(l == 5);
  assert(strcmp(s, "test\n") == 0);

  l = asnprintf(&s, 5, "%s\n", "test");
  assert(l == 5);
  assert(strcmp(s, "test\n") == 0);

  l = asnprintf(&s, 4, "%s\n", "test");
  assert(l == 4);
  assert(strcmp(s, "test") == 0);

  // msprintf

  s = msprintf("%c\n", 'a');
  assert(strlen(s) == 2);
  assert(strcmp(s, "a\n") == 0);
  free(s);

  s = msprintf("%d\n", 123);
  assert(strlen(s) == 4);
  assert(strcmp(s, "123\n") == 0);
  free(s);

  s = msprintf("%s\n", "test");
  assert(strlen(s) == 5);
  assert(strcmp(s, "test\n") == 0);
  free(s);

  // msnprintf

  s = msnprintf(6, "%s\n", "test");
  assert(strlen(s) == 5);
  assert(strcmp(s, "test\n") == 0);

  s = msnprintf(5, "%s\n", "test");
  assert(strlen(s) == 5);
  assert(strcmp(s, "test\n") == 0);

  s = msnprintf(4, "%s\n", "test");
  assert(strlen(s) == 4);
  assert(strcmp(s, "test") == 0);

  // finished

  puts("All tests passed.");

  return 0;
}
