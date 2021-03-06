﻿// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "heap.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "heap/heap_usage_internal.h"
#include "heap_usage.h"

extern uint32_t *heap_area;
extern int heap_area_size;

inline static bool CanAllocate(size_t size) { return heapUsage->Get() <= (heap_area_size - size); }

inline static char *Allocate(size_t size) {
  char *allocated = (char *)(heap_area + heapUsage->Get());
  heapUsage_->Add(size);
  return allocated;
}

char *sbrk(size_t size) { return CanAllocate(size) ? Allocate(size) : (char *)-1; }

static void *New(int size) {
  void *memory = calloc(1, size);
  heapUsage_->WarnIfNeeded();
  return memory;
}

static void Delete(void **memory) {
  if (memory != NULL) {
    free(*memory);
    *memory = NULL;
  }
}

static const HeapMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
};

const HeapMethod heap = &kTheMethod;
