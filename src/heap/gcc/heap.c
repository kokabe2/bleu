﻿// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "heap.h"

#include <malloc.h>
#include <stdlib.h>

static int the_usage = 0;
static int the_usage_for_warning = 0;
static void (*the_warning_func)(int usage) = NULL;

inline static void WarnIfNeeded(void) {
  if (the_warning_func != NULL && the_usage >= the_usage_for_warning)
    the_warning_func(the_usage);
}
static void* New(int size) {
  void* memory = calloc(1, size);
  the_usage += malloc_usable_size(memory);
  WarnIfNeeded();
  return memory;
}
static void Delete(void** memory) {
  the_usage -= malloc_usable_size(*memory);
  free(*memory);
  *memory = NULL;
}
static void ClearUsage(void) { the_usage = 0; }
static void SetUsageWarning(int size, void (*func)(int usage)) {
  the_usage_for_warning = size;
  the_warning_func = func;
}
static const HeapMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
    .ClearUsage = ClearUsage,
    .SetUsageWarning = SetUsageWarning,
};
const HeapMethod heap = &kTheMethod;