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
  EXPECT_STREQ("v2", path->Directory(p, 0));
  EXPECT_STREQ("tickets", path->Directory(p, 1));
  EXPECT_STREQ("12", path->Directory(p, 2));
  EXPECT_STREQ("messages", path->Directory(p, 3));
}
