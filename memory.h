#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

typedef struct MemoryBlock {
  /* A linked list of memory blocks */
  size_t size;
  bool isFree;
  struct MemoryBlock *next;
} MemoryBlock;

#define HEAP_SIZE (1024 * 1024) // 1 MB
#define FREE_ARRAY(type, pointer, oldCount)                                    \
  reallocate(pointer, sizeof(type) * (oldCount), 0)
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)
#define GROW_ARRAY(type, pointer, oldCount, newCount)                          \
  (type *)reallocate(pointer, sizeof(type) * (oldCount),                       \
                     sizeof(type) * newCount)

void initMemory();
void *allocate(size_t size);
void freeMemory(void *ptr);
void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif
