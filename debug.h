#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"
void disasembleChunk(Chunk *chunk, const char *name);
int disasembleInstruction(Chunk *chunk, int offset);
int simpleInstruction(const char *name, int offset);
int constantInstruction(const char *name, Chunk *chunk, int offset);
#endif
