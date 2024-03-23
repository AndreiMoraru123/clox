#ifndef clox__compiler_h
#define clox__compiler_h

#include "vm.h"

bool compile(const char *source, Chunk *chunk);

#endif
