// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "runtime_error.h"
}

class RuntimeErrorTest : public ::testing::Test {
 protected:
  RuntimeError e;

  virtual void SetUp() { e = runtimeError->New(kIllegalArgumentError, "This is just a test.", 1234); }

  virtual void TearDown() { runtimeError->Delete(&e); }
};

TEST_F(RuntimeErrorTest, Category) { EXPECT_EQ(kIllegalArgumentError, runtimeError->Category(e)); }

TEST_F(RuntimeErrorTest, Message) { EXPECT_STREQ("This is just a test.", runtimeError->Message(e)); }

TEST_F(RuntimeErrorTest, Parameter) { EXPECT_EQ(1234, runtimeError->Parameter(e)); }

TEST_F(RuntimeErrorTest, Wrap) {
  runtimeError->Wrap(e, "Additional error");
  runtimeError->Wrap(e, "More error");

  EXPECT_STREQ("More error: Additional error: This is just a test.", runtimeError->Message(e));
}

TEST_F(RuntimeErrorTest, Cause) {
  runtimeError->Wrap(e, "Additional error");
  runtimeError->Wrap(e, "More error");

  EXPECT_STREQ("This is just a test.", runtimeError->Cause(e));
}
