// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "string_builder.h"
}

class StringBuilderTest : public ::testing::Test {
 protected:
  Strings s;
  StringBuilder sb;

  virtual void SetUp() { sb = stringBuilder->New(); }

  virtual void TearDown() { strings->Delete(&s); }
};

TEST_F(StringBuilderTest, Build) {
  stringBuilder->Append(sb, "Alfa Brav")
      ->Append(sb, "o Charlie")
      ->Append(sb, " ")
      ->Append(sb, "Delta Echo Foxtrot Golf");
  s = stringBuilder->ToString(sb);

  EXPECT_STREQ("Alfa Bravo Charlie Delta Echo Foxtrot Golf", s);
}
