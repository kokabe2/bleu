// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_HEAP_USAGE_WARNING_SPY_H_
#define SRC_HEAP_USAGE_WARNING_SPY_H_

#include <stdbool.h>

#include "heap_usage.h"

typedef struct {
  void (*Reset)(void);
  WarningDelegate (*Get)(void);
  bool (*WasRun)(void);
  int (*GivenUsage)(void);
} UsageWarningSpyMethodStruct;
typedef const UsageWarningSpyMethodStruct* UsageWarningSpyMethod;

extern const UsageWarningSpyMethod usageWarningSpy;

#endif  // SRC_HEAP_USAGE_WARNING_SPY_H_
