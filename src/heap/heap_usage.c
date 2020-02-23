// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "heap_usage.h"

#include "stddef.h"

#include "heap_usage_internal.h"

static int the_usage = 0;
static int the_usage_for_warning = 0;
static WarningDelegate the_warning_delegate = NULL;

static void Add(int amount) { the_usage += amount; }
static void Subtract(int amount) { the_usage -= amount; }
static void WarnIfNeeded(void) {
  if (the_warning_delegate && the_usage >= the_usage_for_warning)
    the_warning_delegate(the_usage);
}
static const HeapUsageInternalMethodStruct kInternalMethod = {
    .Add = Add, .Subtract = Subtract, .WarnIfNeeded = WarnIfNeeded,
};
const HeapUsageInternalMethod heapUsage_ = &kInternalMethod;

static int Get(void) { return the_usage; }
static void Clear(void) { the_usage = 0; }
static void SetWarning(int usage, WarningDelegate warning) {
  the_usage_for_warning = usage;
  the_warning_delegate = warning;
}
static const HeapUsageMethodStruct kTheMethod = {
    .Get = Get, .Clear = Clear, .SetWarning = SetWarning,
};
const HeapUsageMethod heapUsage = &kTheMethod;
