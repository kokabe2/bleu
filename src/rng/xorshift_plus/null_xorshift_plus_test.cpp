// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "null_xorshift_plus.h"
}

TEST(NullXorshiftPlusTest, NullObject) {
  uint64_t seeds[] = {1, 2, 3, 4};
  XorshiftPlus self = kNullXorshiftPlus;

  xorshiftPlus->Give(self, seeds);
  EXPECT_EQ(0, xorshiftPlus->Generate(self));
  xorshiftPlus->Delete(&self);

  SUCCEED();
}
