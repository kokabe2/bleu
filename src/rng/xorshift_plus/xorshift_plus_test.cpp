// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include <random>

#include "gtest/gtest.h"

extern "C" {
#include "xorshift128plus.h"
#include "xorshift_plus.h"
}

class XorshiftPlusTest : public ::testing::Test {
 protected:
  uint64_t randoms[1024];
  XorshiftPlus x;
  virtual void SetUp() { x = NULL; }
  virtual void TearDown() { xorshiftPlus->Delete(&x); }
  void AssertRandomness() {
    ASSERT_TRUE(x != NULL);
    for (int i = 0; i < sizeof(randoms) / sizeof(uint64_t); ++i) {
      randoms[i] = xorshiftPlus->Generate(x);
      for (int j = 0; j < i; ++j) ASSERT_NE(randoms[i], randoms[j]);
    }
  }
};

TEST_F(XorshiftPlusTest, XorshiftPlus128) {
  std::random_device rnd;
  uint64_t seeds[] = {rnd(), rnd(), rnd(), rnd()};

  x = xorshift128plus->New();
  xorshiftPlus->Give(x, seeds);

  AssertRandomness();
}

TEST_F(XorshiftPlusTest, Delete) {
  x = xorshift128plus->New();

  xorshiftPlus->Delete(&x);

  ASSERT_EQ(NULL, x);
}

TEST_F(XorshiftPlusTest, DeleteMultipleTimes) {
  x = xorshift128plus->New();

  xorshiftPlus->Delete(&x);
  xorshiftPlus->Delete(&x);

  SUCCEED();
}

TEST_F(XorshiftPlusTest, GiveWithNullSeeds) {
  x = xorshift128plus->New();

  xorshiftPlus->Give(x, NULL);  // No effect

  AssertRandomness();
}

TEST_F(XorshiftPlusTest, GiveWithSeedsAllZero) {
  uint64_t seeds[4] = {0};
  x = xorshift128plus->New();

  xorshiftPlus->Give(x, seeds);  // No effect

  AssertRandomness();
}

TEST_F(XorshiftPlusTest, CallMethodWithNullInstance) {
  uint64_t seeds[] = {1, 2, 3, 4};

  xorshiftPlus->Delete(NULL);
  xorshiftPlus->Give(NULL, seeds);
  EXPECT_EQ(0, xorshiftPlus->Generate(NULL));

  SUCCEED();
}
