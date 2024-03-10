#include "chunk.h"
#include "common.h"
#include "debug.h"

int main(int argc, char *argv[]) {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  int constwo = addConstant(&chunk, 3.5);
  writeChunk(&chunk, OP_CONSTANT, 124);
  writeChunk(&chunk, constwo, 124);

  writeChunk(&chunk, OP_RETURN, 124);
  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);
  return 0;
}
