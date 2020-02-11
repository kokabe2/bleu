// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "heap.h"
#include "heap_usage.h"
#include "usage_warning_spy.h"
}

class HeapTest : public ::testing::Test {
 protected:
  char* c;
  virtual void SetUp() {
    usageWarningSpy->Reset();
    heapUsage->Clear();
    heapUsage->SetWarning(256, usageWarningSpy->Get());
    c = (char*)heap->New(128);
  }
  virtual void TearDown() { heap->Delete((void**)&c); }
};

TEST_F(HeapTest, New) {
  EXPECT_TRUE(c != NULL);
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

TEST_F(HeapTest, HeapUsage) {
  EXPECT_FALSE(usageWarningSpy->WasRun());
  void* v = (void*)heap->New(128);
  EXPECT_TRUE(usageWarningSpy->WasRun());
  EXPECT_GE(usageWarningSpy->GivenUsage(),
            256);  // Actual usage is implementation-dependent.

  heap->Delete((void**)&v);
}
