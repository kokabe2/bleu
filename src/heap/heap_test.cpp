// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "heap.h"
}

namespace {
bool was_run;
int given_usage;
void WarningSpy(int usage) {
  was_run = true;
  given_usage = usage;
}
}  // namespace

class HeapTest : public ::testing::Test {
 protected:
  char* c;
  virtual void SetUp() {
    was_run = false;
    given_usage = 0;
    heap->ClearUsage();
    heap->SetUsageWarning(256, WarningSpy);
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

TEST_F(HeapTest, WarnWhenOverUsageLimit) {
  EXPECT_FALSE(was_run);
  void* v = (void*)heap->New(128);
  EXPECT_TRUE(was_run);
  EXPECT_GE(given_usage, 256);  // Actual usage is implementation-dependent.

  heap->Delete((void**)&v);
}

TEST_F(HeapTest, SetUsageWarningWithNull) {
  heap->SetUsageWarning(256, NULL);

  void* v = (void*)heap->New(128);

  EXPECT_FALSE(was_run);

  heap->Delete((void**)&v);
}

TEST_F(HeapTest, ClearUsage) {
  void* v1 = (void*)heap->New(128);
  was_run = false;

  heap->ClearUsage();
  void* v2 = (void*)heap->New(128);

  EXPECT_FALSE(was_run);

  heap->Delete((void**)&v1);
  heap->Delete((void**)&v2);
}
