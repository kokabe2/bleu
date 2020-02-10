// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "heap_usage.h"
#include "heap_usage_internal.h"
}

namespace {
bool was_run;
int given_usage;
void WarningSpy(int usage) {
  was_run = true;
  given_usage = usage;
}
}  // namespace

class HeapUsageTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    was_run = false;
    given_usage = 0;
    heapUsage->Clear();
    heapUsage->SetWarning(256, WarningSpy);
  }
  virtual void TearDown() {}
};

TEST_F(HeapUsageTest, WarnWhenNotOverUsageLimit) {
  heapUsage_->Add(255);
  heapUsage_->WarnIfNeeded();

  EXPECT_FALSE(was_run);
}

TEST_F(HeapUsageTest, WarnWhenOverUsageLimit) {
  heapUsage_->Add(256);
  heapUsage_->WarnIfNeeded();

  EXPECT_TRUE(was_run);
  EXPECT_EQ(256, given_usage);
}

TEST_F(HeapUsageTest, SetWarningWithNull) {
  heapUsage->SetWarning(255, NULL);

  heapUsage_->Add(256);

  EXPECT_FALSE(was_run);
}

TEST_F(HeapUsageTest, Clear) {
  heapUsage_->Add(255);

  heapUsage->Clear();
  heapUsage_->Add(1);

  EXPECT_FALSE(was_run);
}

TEST_F(HeapUsageTest, SampleTransaction) {
  heapUsage_->Add(192);
  heapUsage_->Subtract(192);
  heapUsage_->Add(100);
  heapUsage_->WarnIfNeeded();
  EXPECT_FALSE(was_run);

  heapUsage_->Add(32);
  heapUsage_->Subtract(32);
  heapUsage_->Add(128);
  heapUsage_->WarnIfNeeded();
  EXPECT_FALSE(was_run);

  heapUsage_->Add(64);
  heapUsage_->WarnIfNeeded();
  EXPECT_TRUE(was_run);
  EXPECT_EQ(292, given_usage);
}
