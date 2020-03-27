// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "heap.h"
#include "heap_usage.h"
#include "usage_warning_spy.h"
}

namespace {
bool was_ran;

void SpyWarning(int unused) { was_ran = true; }
}  // namespace

class HeapTest : public ::testing::Test {
 protected:
  char* c;

  virtual void SetUp() {
    was_ran = false;
    heapUsage->SetWarning(256, SpyWarning);
    heapUsage->Clear();
    c = (char*)heap->New(128);
  }

  virtual void TearDown() { heap->Delete((void**)&c); }
};

TEST_F(HeapTest, New) {
  for (int i = 0; i < 128; ++i) EXPECT_EQ(0, c[i]) << "Failure at index " << i;
}

TEST_F(HeapTest, Delete) {
  heap->Delete((void**)&c);

  EXPECT_EQ(NULL, c);
}

TEST_F(HeapTest, DeleteMultipleTimes) {
  heap->Delete((void**)&c);
  heap->Delete((void**)&c);

  SUCCEED();
}

TEST_F(HeapTest, DeleteWithNull) {
  heap->Delete(NULL);

  SUCCEED();
}

TEST_F(HeapTest, NewWarnsWhenOverUsageLimit) {
  void* v = (void*)heap->New(128);

  EXPECT_TRUE(was_ran);

  heap->Delete((void**)&v);
}
