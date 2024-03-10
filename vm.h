#ifndef clox__vm_h
#define clox__vm_h

#include "chunk.h"

#define STACK_MAX 256

typedef struct {
  Chunk *chunk;
  uint8_t *ip;
  Value stack[STACK_MAX];
  Value *stackTop;
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