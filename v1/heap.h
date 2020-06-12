// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_HEAP_H_
#define V1_HEAP_H_

#include <stddef.h>

typedef struct {
  void* (*New)(int size);
  void (*Delete)(void** memory);
} HeapMethodStruct;
typedef const HeapMethodStruct* HeapMethod;

extern const HeapMethod heap;

#endif  // V1_HEAP_H_
