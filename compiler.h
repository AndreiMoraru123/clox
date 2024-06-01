#ifndef clox__compiler_h
#define clox__compiler_h

#include "object.h"

ObjFunction *compile(const char *source);
void markCompilerRoots();
void incrementRefCount(Obj *object);
void decrementRefCount(Obj *object);

#endif
