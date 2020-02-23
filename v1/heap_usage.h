// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_HEAP_USAGE_H_
#define V1_HEAP_USAGE_H_

typedef void (*WarningDelegate)(int usage);
typedef struct {
  int (*Get)(void);
  void (*Clear)(void);
  void (*SetWarning)(int usage, WarningDelegate warning);
} HeapUsageMethodStruct;
typedef const HeapUsageMethodStruct* HeapUsageMethod;

extern const HeapUsageMethod heapUsage;

#endif  // V1_HEAP_USAGE_H_
