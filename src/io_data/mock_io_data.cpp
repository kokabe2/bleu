// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "mock_io_data.h"

#include <stdint.h>
#include <stdio.h>

#include "gtest/gtest.h"

enum {
  kWrite = 0,
  kAdd,
  kRemove,
  kRead,
};

typedef struct {
  int kind;
  IoAddress offset;
  IoData data;
} ExpectationStruct;

static const struct {
  const char* report_expected;
  const char* report_but_was;
} kExpectedMethodMismatchReports[] = {
    {
        "Expected ioData->Write(0x%x, 0x%x)\n",
        "\t        But was ioData->Write(0x%x, 0x%x)",
    },
    {
        "Expected ioData->Add(0x%x, 0x%x)\n",
        "\t        But was ioData->Add(0x%x, 0x%x)",
    },
    {
        "Expected ioData->Remove(0x%x, 0x%x)\n",
        "\t        But was ioData->Remove(0x%x, 0x%x)",
    },
    {
        "Expected ioData->Read(0x%x) would return 0x%x\n",
        "\t        But was ioData->Read(0x%x) returns 0x%x",
    },
};

static ExpectationStruct* expectations = NULL;
static int set_expectation_count = 0;
static int get_expectation_count = 0;
static int max_expectation_count = 0;
static bool was_failure_already_reported = false;
static ExpectationStruct expected;
static ExpectationStruct actual;

inline static void InitializeExpectations(int expectation_count) {
  if (expectations) free(expectations);
  if (expectation_count > 0)
    expectations = (ExpectationStruct*)calloc(expectation_count,
                                              sizeof(ExpectationStruct));
  else
    expectations = NULL;

  set_expectation_count = 0;
  get_expectation_count = 0;
  max_expectation_count = expectation_count;
  was_failure_already_reported = false;
}
static void SetUp(int expectation_count) {
  InitializeExpectations(expectation_count);
}
inline static void Fail(const char* message) {
  if (was_failure_already_reported) return;
  was_failure_already_reported = true;
  FAIL() << message;
}
inline static void FailWhenNotAllExpectationsUsed(void) {
  if (get_expectation_count == set_expectation_count) return;

  char format[] = "Expected %d but got %d";
  char message[sizeof(format) + 5 + 5];
  snprintf(message, sizeof(message), format, set_expectation_count,
           get_expectation_count);
  Fail(message);
}
static void CleanUp(void) {
  if (!was_failure_already_reported) FailWhenNotAllExpectationsUsed();
  InitializeExpectations(0);
}
inline static bool FailWhenNoRoomForExpectations(const char* message) {
  bool is_failed = (set_expectation_count >= max_expectation_count);
  if (is_failed) Fail(message);
  return is_failed;
}
inline static void RecordExpectation(int kind, IoAddress offset, IoData data) {
  expectations[set_expectation_count].kind = kind;
  expectations[set_expectation_count].offset = offset;
  expectations[set_expectation_count].data = data;
  ++set_expectation_count;
}
static void ExpectWrite(IoAddress offset, IoData data) {
  if (!FailWhenNoRoomForExpectations(
          "mockIoData->ExpectWrite: Too many expectations"))
    RecordExpectation(kWrite, offset, data);
}
static void ExpectAdd(IoAddress offset, IoData data) {
  if (!FailWhenNoRoomForExpectations(
          "mockIoData->ExpectAdd: Too many expectations"))
    RecordExpectation(kAdd, offset, data);
}
static void ExpectRemove(IoAddress offset, IoData data) {
  if (!FailWhenNoRoomForExpectations(
          "mockIoData->ExpectRemove: Too many expectations"))
    RecordExpectation(kRemove, offset, data);
}
static void ExpectReadThenReturn(IoAddress offset, IoData to_return) {
  if (!FailWhenNoRoomForExpectations(
          "mockIoData->ExpectReadThenReturn: Too many expectations"))
    RecordExpectation(kRead, offset, to_return);
}
static const MockIoDataMethodStruct kTheMockMethod = {
    SetUp, CleanUp, ExpectWrite, ExpectAdd, ExpectRemove, ExpectReadThenReturn,
};
const MockIoDataMethod mockIoData = &kTheMockMethod;

static void SetExpectedAndActual(int kind, IoAddress offset, IoData data) {
  expected = expectations[get_expectation_count];
  actual.kind = kind;
  actual.offset = offset;
  actual.data = data;
}

static void FailWhenNoUnusedExpectations(const char* format) {
  if (get_expectation_count < set_expectation_count) return;

  char message[100];
  int size = sizeof(message) - 1;
  int offset =
      snprintf(message, size, "Count %d: No more expectations but was ",
               get_expectation_count + 1);
  snprintf(message + offset, size - offset, format, actual.offset, actual.data);
  Fail(message);
}

static bool ExpectedMatchesActual(void) {
  return (actual.kind == expected.kind) && (actual.offset == expected.offset) &&
         ((actual.data == expected.data) || (actual.data == kNoExpectedValue) ||
          (expected.data == kNoExpectedValue));
}

static void FailWhenExpectedDoesNotMatch(void) {
  if (ExpectedMatchesActual()) return;

  char message[128];
  int size = sizeof(message) - 1;
  int offset = snprintf(message, size, "Count %d: ", get_expectation_count + 1);
  offset +=
      snprintf(message + offset, size - offset,
               kExpectedMethodMismatchReports[expected.kind].report_expected,
               expected.offset, expected.data);
  offset += snprintf(message + offset, size - offset,
                     kExpectedMethodMismatchReports[actual.kind].report_but_was,
                     actual.offset, actual.data);
  Fail(message);
}

static void Write(IoAddress offset, IoData data) {
  if (!expectations) return;

  SetExpectedAndActual(kWrite, offset, (IoData)data);
  FailWhenNoUnusedExpectations("ioData->Write(0x%x, 0x%x)");
  FailWhenExpectedDoesNotMatch();
  ++get_expectation_count;
}
static void Write8bit(IoAddress offset, IoData data) {
  Write(offset, (uint8_t)data);
}
static void Write16bit(IoAddress offset, IoData data) {
  Write(offset, (uint16_t)data);
}
static void Write32bit(IoAddress offset, IoData data) {
  Write(offset, (uint32_t)data);
}
static void Add(IoAddress offset, IoData data) {
  if (!expectations) return;

  SetExpectedAndActual(kAdd, offset, (IoData)data);
  FailWhenNoUnusedExpectations("ioData->Add(0x%x, 0x%x)");
  FailWhenExpectedDoesNotMatch();
  ++get_expectation_count;
}
static void Add8bit(IoAddress offset, IoData data) {
  Add(offset, (uint8_t)data);
}
static void Add16bit(IoAddress offset, IoData data) {
  Add(offset, (uint16_t)data);
}
static void Add32bit(IoAddress offset, IoData data) {
  Add(offset, (uint32_t)data);
}
static void Remove(IoAddress offset, IoData data) {
  if (!expectations) return;

  SetExpectedAndActual(kRemove, offset, (IoData)data);
  FailWhenNoUnusedExpectations("ioData->Remove(0x%x, 0x%x)");
  FailWhenExpectedDoesNotMatch();
  ++get_expectation_count;
}
static void Remove8bit(IoAddress offset, IoData data) {
  Remove(offset, (uint8_t)data);
}
static void Remove16bit(IoAddress offset, IoData data) {
  Remove(offset, (uint16_t)data);
}
static void Remove32bit(IoAddress offset, IoData data) {
  Remove(offset, (uint32_t)data);
}
static IoData Read(IoAddress offset) {
  if (!expectations) return 0;

  SetExpectedAndActual(kRead, offset, kNoExpectedValue);
  FailWhenNoUnusedExpectations("ioData->Read(0x%x)");
  FailWhenExpectedDoesNotMatch();
  return expectations[get_expectation_count++].data;
}
static IoData Read8bit(IoAddress offset) { return (uint8_t)Read(offset); }
static IoData Read16bit(IoAddress offset) { return (uint16_t)Read(offset); }
static IoData Read32bit(IoAddress offset) { return (uint32_t)Read(offset); }
static const IoInterfaceStruct kImplFor8bit = {
    Write8bit, Add8bit, Remove8bit, Read8bit,
};
static const IoInterfaceStruct kImplFor16bit = {
    Write16bit, Add16bit, Remove16bit, Read16bit,
};
static const IoInterfaceStruct kImplFor32bit = {
    Write32bit, Add32bit, Remove32bit, Read32bit,
};
static const IoDataMethodStruct kTheMethod = {
    &kImplFor8bit, &kImplFor16bit, &kImplFor32bit,
};
const IoDataMethod ioData = &kTheMethod;
