// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "path.h"
}

class PathTest : public ::testing::Test {
 protected:
  Path p;

  virtual void SetUp() { p = path->New("v2/tickets/12/messages"); }

  virtual void TearDown() { path->Delete(&p); }
};

TEST_F(PathTest, Count) { EXPECT_EQ(4, path->Count(p)); }

TEST_F(PathTest, Directory) {
  Strings s0 = path->Directory(p, 0);
  Strings s1 = path->Directory(p, 1);
  Strings s2 = path->Directory(p, 2);
  Strings s3 = path->Directory(p, 3);

  EXPECT_STREQ("v2", s0);
  EXPECT_STREQ("tickets", s1);
  EXPECT_STREQ("12", s2);
  EXPECT_STREQ("messages", s3);

  strings->Delete(&s0);
  strings->Delete(&s1);
  strings->Delete(&s2);
  strings->Delete(&s3);
}
