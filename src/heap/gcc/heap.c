// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "heap.h"

#include <malloc.h>
#include <stdlib.h>

#include "../heap_usage_internal.h"

static void* New(int size) {
  void* memory = calloc(1, size);
  heapUsage_->Add(malloc_usable_size(memory));
  heapUsage_->WarnIfNeeded();
  return memory;
}
static void Delete(void** memory) {
  if (!memory) return;
  heapUsage_->Subtract(malloc_usable_size(memory));
  free(*memory);
  *memory = NULL;
}
static const HeapMethodStruct kTheMethod = {
    .New = New, .Delete = Delete,
};
const HeapMethod heap = &kTheMethod;
