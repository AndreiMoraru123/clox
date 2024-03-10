#include "stdlib.h"
#include <stdint.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines = NULL;
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code =
        GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

void writeConstant(Chunk *chunk, Value value, int line) {
  int constantIndex = addConstant(chunk, value);

  if (constantIndex < 256) {
    writeChunk(chunk, OP_CONSTANT, line);
    writeChunk(chunk, (uint8_t)constantIndex, line);
  } else {
    /* Requires more than one byte, using long */
    writeChunk(chunk, OP_CONSTANT_LONG, line);
    /* Split the 25-bit index into three bites */
    /* 0xff is 255 in decimal, and 11111111 in binary, therefore & 0xff
     * masks all but the lowest 8 bits of the number. As such, shifting right
     * by 16 bits will assure the most significant 8 out of the 24-bit number
     * are selected, so this is the high byte out of the three, and so on
     *
     * Example:
     *
     * High Byte:
     *   0x123456 >> 16 is 0x12.
     *   0x12 & 0xff is 0x12.
     *
     * Middle Byte:
     *   0x123456 >> 8 is 0x1234.
     *   0x1234 & 0xff is 0x34.
     *
     * Low Byte:
     *   0x123456 & 0xff is 0x56.
     */
    writeChunk(chunk, (constantIndex >> 16) & 0xff, line); // high byte
    writeChunk(chunk, (constantIndex >> 8) & 0xff, line);  // middle byte
    writeChunk(chunk, constantIndex & 0xff, line);         // low byte
  }
}
