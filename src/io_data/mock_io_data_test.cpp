// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest-spi.h"
#include "gtest/gtest.h"

#include "mock_io_data.h"

class MockIoDataTest : public ::testing::Test {
 protected:
  virtual void SetUp() { mockIoData.SetUp(4); }
  virtual void TearDown() { mockIoData.CleanUp(); }
};

TEST_F(MockIoDataTest, CanMatchExpectation) {
  mockIoData.ExpectWrite(1, 2);
  mockIoData.ExpectAdd(1, 9);
  mockIoData.ExpectRemove(1, 1);
  mockIoData.ExpectReadThenReturn(1, 10);

  ioData.b8.Write(1, 2);
  ioData.b8.Add(1, 9);
  ioData.b8.Remove(1, 1);
  uint8_t data = ioData.b8.Read(1);

  EXPECT_EQ(10, data);
}

TEST_F(MockIoDataTest, WriteWhenReadExpectedFails) {
  mockIoData.ExpectReadThenReturn(0, 1);
  EXPECT_FATAL_FAILURE(
      ioData.b8.Write(0, 0),
      "Count 1: Expected ioData.Read(0x0) would return 0x1\n\t        "
      "But was ioData.Write(0x0, 0x0)");
}

TEST_F(MockIoDataTest, ReadWhenWriteExpectedFails) {
  mockIoData.ExpectWrite(0, 1);
  EXPECT_FATAL_FAILURE(ioData.b8.Read(0),
                       "Count 1: Expected ioData.Write(0x0, 0x1)\n\t        "
                       "But was ioData.Read(0x0)");
}

TEST_F(MockIoDataTest, TooManyWriteExpectations) {
  mockIoData.ExpectWrite(0, 1);
  mockIoData.ExpectWrite(0, 1);
  mockIoData.ExpectWrite(0, 1);
  mockIoData.ExpectWrite(0, 1);
  EXPECT_FATAL_FAILURE(mockIoData.ExpectWrite(0, 1),
                       "mockIoData.ExpectWrite: Too many expectations");
}

TEST_F(MockIoDataTest, TooManyReadExpectations) {
  mockIoData.ExpectReadThenReturn(0, 0);
  mockIoData.ExpectReadThenReturn(0, 0);
  mockIoData.ExpectReadThenReturn(0, 0);
  mockIoData.ExpectReadThenReturn(0, 0);
  EXPECT_FATAL_FAILURE(
      mockIoData.ExpectReadThenReturn(0, 0),
      "mockIoData.ExpectReadThenReturn: Too many expectations");
}

TEST_F(MockIoDataTest, MismatchedWriteAddress) {
  mockIoData.ExpectWrite(0, 0);
  EXPECT_FATAL_FAILURE(ioData.b8.Write(0x10, 0),
                       "Count 1: Expected ioData.Write(0x0, 0x0)\n\t        "
                       "But was ioData.Write(0x10, 0x0)");
}

TEST_F(MockIoDataTest, MismatchedWriteData) {
  mockIoData.ExpectWrite(0, 0);
  EXPECT_FATAL_FAILURE(ioData.b8.Write(0, 0xde),
                       "Count 1: Expected ioData.Write(0x0, 0x0)\n\t        "
                       "But was ioData.Write(0x0, 0xde)");
}

TEST_F(MockIoDataTest, MismatchedReadAddress) {
  mockIoData.ExpectReadThenReturn(0x1000, 0xaa);
  EXPECT_FATAL_FAILURE(
      ioData.b8.Read(0x10000),
      "Count 1: Expected ioData.Read(0x1000) would return 0xaa\n\t        "
      "But was ioData.Read(0x10000)");
}

TEST_F(MockIoDataTest, TooManyReads) {
  EXPECT_FATAL_FAILURE(
      ioData.b8.Read(0x10000),
      "Count 1: No more expectations but was ioData.Read(0x10000)");
}

TEST_F(MockIoDataTest, TooManyWrites) {
  EXPECT_FATAL_FAILURE(
      ioData.b8.Write(0x10000, 0x12),
      "Count 1: No more expectations but was ioData.Write(0x10000, 0x12)");
}

TEST_F(MockIoDataTest, NotAllExpectationsUsed) {
  mockIoData.ExpectReadThenReturn(0x1000, 0xaa);
  mockIoData.ExpectWrite(0x1000, 0x55);
  EXPECT_FATAL_FAILURE(mockIoData.CleanUp(), "Expected 2 but got 0");
}

TEST_F(MockIoDataTest, WriteNoExpectedData) {
  mockIoData.ExpectWrite(0, kNoExpectedValue);
  ioData.b32.Write(0, 0xdeadbeef);
}
