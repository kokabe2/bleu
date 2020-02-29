// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include <random>

#include "gtest/gtest.h"

extern "C" {
#include "xorshift.h"
#include "xorshift128.h"
#include "xorshift32.h"
#include "xorshift64.h"
#include "xorshift96.h"
}

class XorshiftTest : public ::testing::Test {
 protected:
  uint32_t randoms[1024];
  Xorshift x;

  virtual void SetUp() { x = NULL; }

  virtual void TearDown() {
    if (x != NULL) xorshift->Delete(&x);
  }

  void AssertRandomness() {
    for (int i = 0; i < sizeof(randoms) / sizeof(uint32_t); ++i) {
      randoms[i] = xorshift->Generate(x);
      for (int j = 0; j < i; ++j) ASSERT_NE(randoms[i], randoms[j]);
    }
  }
};

TEST_F(XorshiftTest, Xorshift32) {
  std::random_device rnd;
  uint32_t seeds[] = {rnd()};

  x = xorshift32->New();
  xorshift->Give(x, seeds);

  AssertRandomness();
}

TEST_F(XorshiftTest, Xorshift64) {
  std::random_device rnd;
  uint32_t seeds[] = {rnd(), rnd()};

  x = xorshift64->New();
  xorshift->Give(x, seeds);

  AssertRandomness();
}

TEST_F(XorshiftTest, Xorshift96) {
  std::random_device rnd;
  uint32_t seeds[] = {rnd(), rnd(), rnd()};

  x = xorshift96->New();
  xorshift->Give(x, seeds);

  AssertRandomness();
}

TEST_F(XorshiftTest, Xorshift128) {
  std::random_device rnd;
  uint32_t seeds[] = {rnd(), rnd(), rnd(), rnd()};

  x = xorshift128->New();
  xorshift->Give(x, seeds);

  AssertRandomness();
}

TEST_F(XorshiftTest, Delete) {
  x = xorshift64->New();

  xorshift->Delete(&x);

  ASSERT_EQ(NULL, x);
}

TEST_F(XorshiftTest, GiveWithSeedsAllZero) {
  uint32_t seeds[4] = {0};
  x = xorshift128->New();

  xorshift->Give(x, seeds);  // No effect

  AssertRandomness();
}
