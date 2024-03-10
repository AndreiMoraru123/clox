#include "stdlib.h"
#include <stdint.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  chunk->lineCount = 0;
  chunk->lineCapacity = 0;
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(LineStart, chunk->lines, chunk->lineCapacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code =
        GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
  }

  /* Run-length encoding the line counter means that instead of storing every
   * line for every byte of bytecode, we can instead store the line number only
   * when it changes, which will reduce memory usage (data compression) */

  if (chunk->count == 0 || chunk->lines[chunk->lineCount - 1].line != line) {

    /* Either the count is 0, so the chunk is empty of bytecode, then we need to
     * start tracking line info at this point, OR the current line number is
     * different from the line number of the last entry in the lines array which
     * as well means a new LineStart entry is needed to record the change */

    if (chunk->lineCapacity < chunk->lineCount + 1) {
      int oldLineCapacity = chunk->lineCapacity;
      chunk->lineCapacity = GROW_CAPACITY(oldLineCapacity);
      chunk->lines = GROW_ARRAY(LineStart, chunk->lines, oldLineCapacity,
                                chunk->lineCapacity);
    }

    LineStart newLineStart = {line, chunk->count};
    chunk->lines[chunk->lineCount] = newLineStart;
    chunk->lineCount++;
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}
