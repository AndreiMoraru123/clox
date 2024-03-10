#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassembleChunk(Chunk *chunk, const char *name) {
  printf("== %s ==\n", name);

  for (int offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

int getLine(Chunk *chunk, int index) {
  /* Performs binary search over the lines array (which is sorted by startByte).
   *
   * Each LineStart element in the lines marks the beginning of a new line
   * number at a certain byte code index (offset).
   *
   * When we look for the line number corresponding to a specific bytecode
   * index, we know that if a LineStart has a startBytes less than our equal to
   * our target index, the line number for that LineStart is a potential match.
   */
  int start = 0;
  int end = chunk->lineCount - 1;

  while (start <= end) {
    int mid = (start + end) / 2;
    LineStart *lineStart = &chunk->lines[mid];

    if (index < lineStart->startByte) {
      /* If the current byte code offset is less than the startByte of the mid,
       * it means we need to search the left half of the array (ignore right) */
      end = mid - 1;
    } else if (mid == chunk->lineCount - 1 ||
               index < chunk->lines[mid + 1].startByte) {
      /* If mid is the last element in the array (chunk->lineCount -1), we've
       * found the line number since there is no next element to compare with.
       *
       * Also, if the next element's startByte is greater than the index, the
       * current mid is the correct pick, because it's the last LineStart whose
       * startByte is less than or equal to our index */
      return lineStart->line;
    } else {
      /* Search the right half of the array (ignore left) */
      start = mid + 1;
    }
  }

  return -1;
}

int disassembleInstruction(Chunk *chunk, int offset) {
  printf("%04d", offset);
  int currentLine = getLine(chunk, offset);
  printf("%4d ", currentLine);
  uint8_t instruction = chunk->code[offset];
  switch (instruction) {
  case OP_CONSTANT:
    return constantInstruction("OP_CONSTANT", chunk, offset);
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

int simpleInstruction(const char *name, int offset) {
  printf("%s\n", name);
  return offset + 1;
}
