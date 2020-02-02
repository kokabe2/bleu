// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "null_xorshift.h"
}

TEST(NullXorshiftTest, NullObject) {
  uint32_t seeds[] = {1, 2, 3, 4};
  Xorshift self = kNullXorshift;

  xorshift->Give(self, seeds);
  EXPECT_EQ(0, xorshift->Generate(self));
  xorshift->Delete(&self);

  SUCCEED();
}
