#include "memory.h"
#include <stdlib.h>
#include <string.h>

static char *heap;
static MemoryBlock *freeList = NULL;

void initMemory() {
  /* Initial dynamic heap allocation */
  heap = (char *)malloc(HEAP_SIZE);
  if (heap == NULL) {
    exit(1);
  }

  freeList = (MemoryBlock *)heap;
  freeList->size = HEAP_SIZE - sizeof(MemoryBlock);
  freeList->isFree = true;
  freeList->next = NULL;
}

void *allocate(size_t size) {
  MemoryBlock *curr = freeList;

  while (curr) {
    /* Checks if the current block is free and big enough to allocate the
     * requested size */
    if (curr->isFree && curr->size >= size) {

      /* Checks if the current block is larger than what is needed.
       * If so, then the block can be split into two parts:
       *  - one to extract the exact requested size
       *  - one to for the remaining memory
       */
      if (curr->size > size + sizeof(MemoryBlock)) {

        /* Finds the start of the memory block, by subtracting the sizeof it */
        MemoryBlock *newBlock =
            (MemoryBlock *)((char *)curr + sizeof(MemoryBlock) + size);

        /* Sets up the new block
         *  - mark its size the remaining after allocating size bytes from curr
         *  - mark it as free
         *  - mark its next pointer to the next block in the list
         */
        newBlock->size = curr->size - size - sizeof(MemoryBlock);
        newBlock->isFree = true;
        newBlock->next = curr->next;

        /* Updates the current block
         *  - mark its size as the allocated size
         *  - mark its next pointer to point to newBlock, which means inserting
         *  newBlock into the freeList
         */
        curr->size = size;
        curr->next = newBlock;
      }

      /* Marks the current block as no longer free */
      curr->isFree = false;

      /* Returns a pointer to the usable memory of the allocated block
       *  No casting to (MemoryBlock *) here intentionally to skip the metadata
       *  providing a pointer to just where the memory allocation starts
       */
      return (char *)curr + sizeof(MemoryBlock);
    }

    curr = curr->next;
  }
  return NULL;
}

void freeMemory(void *ptr) {
  if (!ptr)
    return;

  /* Finds the start of the memory block, by subtracting the sizeof it */
  MemoryBlock *block = (MemoryBlock *)((char *)ptr - sizeof(MemoryBlock));
  block->isFree = true;
}

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    /* if the desired newSize is null, just free the memory */
    freeMemory(pointer);
    return NULL;
  }

  if (!pointer) {
    /* if the pointer is NULL, the function acts like malloc */
    return allocate(newSize); // no need to copy data
  }

  /* Finds the start of the memory block, by subtracting the sizeof it */
  MemoryBlock *block = (MemoryBlock *)((char *)pointer - sizeof(MemoryBlock));
  if (block->size >= newSize) {
    /* if the block of memory currently pointed at by the pointer is large
     * enough to hold newSize, simply return the same pointer. This is an
     * optimization to avoid unnecessary memory copying.
     */
    return pointer;
  }

  /* if the block current block is not large enough, allocate a new one */
  void *newBlock = allocate(newSize); // need to copy data
  if (!newBlock) {
    return NULL;
  }

  memcpy(newBlock, pointer, block->size);
  freeMemory(pointer);
  return newBlock;
}
