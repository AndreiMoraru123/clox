#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, char *argv[]) {
  initVM();

  Chunk chunk;
  initChunk(&chunk);

  // 4 - 3 * -2

  // Negate 3
  int constant = addConstant(&chunk, 3);
  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant, 1);
  writeChunk(&chunk, OP_NEGATE, 1);

  // Negate 2
  constant = addConstant(&chunk, 2);
  writeChunk(&chunk, OP_CONSTANT, 1);
  writeChunk(&chunk, constant, 1);
  writeChunk(&chunk, OP_NEGATE, 1);

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
