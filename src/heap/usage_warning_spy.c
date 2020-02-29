// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "usage_warning_spy.h"

static bool was_run;
static int given_usage;

static void Reset(void) {
  was_run = false;
  given_usage = 0;
}

static void WarningSpy(int usage) {
  was_run = true;
  given_usage = usage;
}

static WarningDelegate Get(void) { return WarningSpy; }

static bool WasRun(void) { return was_run; }

static int GivenUsage(void) { return given_usage; }

static const UsageWarningSpyMethodStruct kTheMethod = {
    .Reset = Reset, .Get = Get, .WasRun = WasRun, .GivenUsage = GivenUsage,
};

const UsageWarningSpyMethod usageWarningSpy = &kTheMethod;
