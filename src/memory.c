#include "memory.h"
#include "stdio.h"
#include "vm.h"
#include <stdlib.h>

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void *result = realloc(pointer, newSize);
  if (result == NULL) {
    perror("realloc(): failed to reallocate memory for bytecode Chunk\n");
    exit(1);
  }

  return result;
}
