// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "heap_usage.h"
#include "heap_usage_internal.h"
#include "usage_warning_spy.h"
}

namespace {
bool was_ran;
int given_usage;

void SpyWarning(int usage) {
  was_ran = true;
  given_usage = usage;
}
}  // namespace

class HeapUsageTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    was_ran = false;
    given_usage = 0;
    heapUsage->SetWarning(256, SpyWarning);
    heapUsage->Clear();
  }

  virtual void TearDown() {}
};

TEST_F(HeapUsageTest, Get) {
  heapUsage_->Add(128);
  heapUsage_->Subtract(6);
  heapUsage_->Add(45);

  EXPECT_EQ(167, heapUsage->Get());
}

TEST_F(HeapUsageTest, Clear) {
  heapUsage_->Add(1000);

  heapUsage->Clear();

  EXPECT_EQ(0, heapUsage->Get());
}

TEST_F(HeapUsageTest, WarnWhenNotOverUsageLimit) {
  heapUsage_->Add(255);

  heapUsage_->WarnIfNeeded();

  EXPECT_FALSE(was_ran);
}

TEST_F(HeapUsageTest, WarnWhenOverUsageLimit) {
  heapUsage_->Add(256);

  heapUsage_->WarnIfNeeded();

  EXPECT_TRUE(was_ran);
  EXPECT_EQ(256, given_usage);
}

TEST_F(HeapUsageTest, SampleTransaction) {
  heapUsage_->Add(192);
  heapUsage_->Subtract(192);
  heapUsage_->Add(100);
  heapUsage_->WarnIfNeeded();
  EXPECT_EQ(100, heapUsage->Get());
  EXPECT_FALSE(was_ran);

  heapUsage_->Add(32);
  heapUsage_->Subtract(32);
  heapUsage_->Add(128);
  heapUsage_->WarnIfNeeded();
  EXPECT_EQ(228, heapUsage->Get());
  EXPECT_FALSE(was_ran);

  heapUsage_->Add(64);
  heapUsage_->WarnIfNeeded();
  EXPECT_EQ(292, heapUsage->Get());
  EXPECT_TRUE(was_ran);
  EXPECT_EQ(292, given_usage);
}
