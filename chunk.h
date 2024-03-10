#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_RETURN,
} OpCode;

typedef struct {
  int line;
  int startByte;
} LineStart;

typedef struct {
  int count;
  int capacity;
  uint8_t *code;
  ValueArray constants;
  LineStart *lines;
  int lineCount;
  int lineCapacity;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
int addConstant(Chunk *chunk, Value value);

#endif
