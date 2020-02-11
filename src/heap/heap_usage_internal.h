// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_HEAP_HEAP_USAGE_INTERNAL_H_
#define SRC_HEAP_HEAP_USAGE_INTERNAL_H_

typedef struct {
  int (*Get)(void);
  void (*Add)(int amount);
  void (*Subtract)(int amount);
  void (*WarnIfNeeded)(void);
} HeapUsageInternalMethodStruct;
typedef const HeapUsageInternalMethodStruct* HeapUsageInternalMethod;

extern const HeapUsageInternalMethod heapUsage_;

#endif  // SRC_HEAP_HEAP_USAGE_INTERNAL_H_
