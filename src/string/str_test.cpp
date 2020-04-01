// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "str.h"
}

class StringsTest : public ::testing::Test {
 protected:
  Strings s;

  virtual void SetUp() { s = strings->New("Alfa Bravo Charlie Delta Echo Foxtrot Golf"); }

  virtual void TearDown() { strings->Delete(&s); }
};

TEST_F(StringsTest, NewReturnsOtherInstance) { EXPECT_NE("Alfa Bravo Charlie Delta Echo Foxtrot Golf", s); }

TEST_F(StringsTest, Length) { EXPECT_EQ(42, strings->Length(s)); }

TEST_F(StringsTest, EqualsWithSameStrings) {
  EXPECT_TRUE(strings->Equals(s, "Alfa Bravo Charlie Delta Echo Foxtrot Golf"));
}

TEST_F(StringsTest, EqualsWithDifferentStrings) {
  EXPECT_FALSE(strings->Equals(s, "Alfa Bravo Charlie Delta EchO Foxtrot Golf"));
}

TEST_F(StringsTest, EqualsWithSameUntilHalfway) {
  EXPECT_FALSE(strings->Equals(s, "Alfa Bravo Charlie Delta Echo Foxtrot Golf."));
}

TEST_F(StringsTest, Contains) { EXPECT_TRUE(strings->Contains(s, "Delta")); }

TEST_F(StringsTest, ContainsWhenNotContains) { EXPECT_FALSE(strings->Contains(s, "Hotel")); }

TEST_F(StringsTest, Index) { EXPECT_EQ(19, strings->Index(s, "Delta")); }

TEST_F(StringsTest, IndexWhenNotContains) { EXPECT_EQ(-1, strings->Index(s, "Hotel")); }

TEST_F(StringsTest, LastIndex) { EXPECT_EQ(23, strings->LastIndex(s, "a")); }

TEST_F(StringsTest, LastIndexWhenNotContains) { EXPECT_EQ(-1, strings->LastIndex(s, "Hotel")); }

TEST_F(StringsTest, Count) { EXPECT_EQ(4, strings->Count(s, "a")); }

TEST_F(StringsTest, CountWhenNotContains) { EXPECT_EQ(0, strings->Count(s, "Hotel")); }

TEST_F(StringsTest, HasPrefix) { EXPECT_TRUE(strings->HasPrefix(s, "Alfa")); }

TEST_F(StringsTest, HasPrefixWhenNotPrefix) { EXPECT_FALSE(strings->HasPrefix(s, "Golf")); }

TEST_F(StringsTest, HasPrHasSuffixefix) { EXPECT_TRUE(strings->HasSuffix(s, "Golf")); }

TEST_F(StringsTest, HasSuffixWhenNotSuffix) { EXPECT_FALSE(strings->HasSuffix(s, "Bravo")); }
