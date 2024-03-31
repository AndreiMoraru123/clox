#ifndef clox__vm_h
#define clox__vm_h

#include "chunk.h"
#include "table.h"
#include "value.h"

#define STACK_MAX 256

typedef struct {
  Chunk *chunk;
  uint8_t *ip;
  Value stack[STACK_MAX];
  Value *stackTop;
  Table strings;
  Table globals;
  Obj *objects;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
} InterpreterResult;

extern VM vm;

void initVM();
void freeVM();
InterpreterResult interpret(const char *source);
void push(Value value);
Value pop();

#endif
