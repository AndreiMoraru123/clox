#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, char *argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  // 4 - 3 * -2

  // Load 0
  int constant = addConstant(&chunk, 0);
  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant, 1);

  // Load 3
  constant = addConstant(&chunk, 3);
  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant, 1);

  // 0 - 3 = -3
  writeChunk(&chunk, OP_SUBTRACT, 1);

  // Load 0
  constant = addConstant(&chunk, 0);
  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant, 1);

  // Load 2
  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant, 1);

  // 0 - 2 = -2
  writeChunk(&chunk, OP_SUBTRACT, 1);

  // Multiply -3 by -2
  writeChunk(&chunk, OP_MULTIPLY, 1);

  // Add 4
  constant = addConstant(&chunk, 4);
  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant, 1);

  writeChunk(&chunk, OP_ADD, 1);

  writeChunk(&chunk, OP_RETURN, 123);
  disassembleChunk(&chunk, "test chunk");
  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}
