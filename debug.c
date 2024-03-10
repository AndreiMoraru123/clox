#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk *chunk, const char *name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

int disassembleInstruction(Chunk *chunk, int offset) {
  printf("%04d", offset);
  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
    printf("   | ");
  } else {
    printf("%4d ", chunk->lines[offset]);
  }
  uint8_t instruction = chunk->code[offset];

  switch (instruction) {
  case OP_CONSTANT:
    return constantInstruction("OP_CONSTANT", chunk, offset);
  case OP_CONSTANT_LONG:
    return constantInstructionLong("OP_CONSTANT_LONG", chunk, offset);
  case OP_RETURN:
    return simpleInstruction("OP_RETURN", offset);
  default:
    printf("Unknown opcode %d\n", instruction);
    return offset + 1;
  }
}

int constantInstruction(const char *name, Chunk *chunk, int offset) {
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  return offset + 2;
}

int constantInstructionLong(const char *name, Chunk *chunk, int offset) {
  /* Example:
   *
   * chunk->code[offset + 1] == 0x01
   * chunk->code[offset + 2] == 0x02
   * chunk->code[offset + 3] == 0x03
   *
   * which we want to combine into a single number
   *
   * 0x01 << 16 (shifted left by 16) becomes 0x010000
   * 0x02 << 8 (shifted left by 8) becomes 0x0200
   * 0x03 does not need shifting because it's already the least significant byte
   *
   * Combined using bitwise OR, they result in the hexadecimal 0x010203
   */
  int constantIndex = (chunk->code[offset + 1] << 16) |
                      (chunk->code[offset + 2] << 8) |
                      (chunk->code[offset + 3]);
  printf("%-16s %4d '", name, constantIndex);
  printValue(chunk->constants.values[constantIndex]);
  printf("'\n");
  return offset + 4; // 8 x (3 + 1)
}

int simpleInstruction(const char *name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}
