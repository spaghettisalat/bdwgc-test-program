#include <gc/gc.h>
#include "alloc.h"

struct test_struct *alloc_test_struct(void *a, void *b) {
  struct test_struct *obj;
  obj = GC_MALLOC(sizeof(struct test_struct));
  obj->a = a;
  obj->b = b;
  return obj;
}

