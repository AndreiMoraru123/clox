#ifndef clox__vm_h
#define clox__vm_h

#include "chunk.h"

typedef struct {
  Chunk *chunk;
  uint8_t *ip;
  Value *stack;
  Value *stackTop;
  int stackCapacity;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpreterResult;

void initVM();
void freeVM();
InterpreterResult interpret(Chunk *chunk);
void push(Value value);
Value pop();

#endif
