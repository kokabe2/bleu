// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_MOCK_IO_DATA_H_
#define V1_MOCK_IO_DATA_H_

extern "C" {
#include "io_data.h"
}

enum {
  kNoExpectedValue = ~0,
};

typedef uint32_t IoData;

typedef struct {
  void (*SetUp)(int expectation_count);
  void (*CleanUp)(void);
  void (*ExpectWrite)(IoAddress offset, IoData data);
  void (*ExpectAdd)(IoAddress offset, IoData data);
  void (*ExpectRemove)(IoAddress offset, IoData data);
  void (*ExpectReadThenReturn)(IoAddress offset, IoData to_return);
} MockIoDataMethodStruct;
typedef const MockIoDataMethodStruct *MockIoDataMethod;

extern const MockIoDataMethod mockIoData;

#endif  // V1_MOCK_IO_DATA_H_
