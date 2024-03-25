#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

static ObjString *allocateString(char *chars, int length) {
  ObjString *string =
      (ObjString *)reallocate(NULL, 0, sizeof(ObjString) + length + 1);
  string->obj.type = OBJ_STRING;
  string->length = length;

  memcpy(string->chars, chars, length);
  string->chars[length] = '\0';

  string->obj.next = vm.objects;
  vm.objects = (Obj *)string;
  return string;
}

ObjString *takeString(char *chars, int length) {
  return allocateString(chars, length);
}

ObjString *copyString(const char *chars, int length) {
  char *heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return allocateString(heapChars, length);
}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
  case OBJ_STRING:
    printf("%s", AS_CSTRING(value));
    break;
  }
}