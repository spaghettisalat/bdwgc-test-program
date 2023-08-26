#include <stdio.h>
#include <assert.h>
#include <windows.h>
#define GC_THREADS
#include <gc/gc.h>
#include "alloc.h"

#define len 128
#define repetitions 4096
#define num_threads 2

DWORD test_fun(void *arg) {
  int *a = ((int**)arg)[0];
  int *b = ((int**)arg)[1];
  struct test_struct *array[len];
  for (int k = 0; k < repetitions; k++) {
    for (int i = 0; i < len; i++) {
      array[i] = alloc_test_struct(alloc_test_struct(a+i, a+i), b+i);
    }
    for (int i = 0; i < len; i++) {
      assert(*((int*) ((struct test_struct*) array[i]->a)->a) == i);
      assert(*((int*) ((struct test_struct*) array[i]->a)->b) == i);
      assert(*((int*) array[i]->b) == -i);
    }
  }
  return EXIT_SUCCESS;
}

void start_threads() {
  int a[len];
  int b[len];
  for (int i = 0; i < len; i++) {
    a[i] = i;
    b[i] = -i;
  }
  int *arg[2];
  arg[0] = a;
  arg[1] = b;
  HANDLE thread_handles[num_threads];
  for (int i = 0; i < num_threads; i++) {
    DWORD threadId;
    thread_handles[i] = (HANDLE)GC_CreateThread(NULL, 0, test_fun, (void*)arg, 0, &threadId);
    assert(thread_handles[i] != NULL);
  }
  for (int i = 0; i < num_threads; i++) {
    assert(WaitForSingleObject(thread_handles[i], INFINITE) == WAIT_OBJECT_0);
  }  
}

int main() {
  GC_init();
  start_threads();
}
