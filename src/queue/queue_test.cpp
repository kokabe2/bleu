// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "queue.h"
}

class QueueTest : public ::testing::Test {
 protected:
  Queue q;
  virtual void SetUp() { q = queue->New(32); }
  virtual void TearDown() { queue->Delete(&q); }
  void AssertInitialCondition() {
    ASSERT_TRUE(q != NULL);
    EXPECT_EQ(0, queue->UsedSize(q));
    EXPECT_EQ(32, queue->AvailableSize(q));
  }
};

TEST_F(QueueTest, ConditionAfterNew) { AssertInitialCondition(); }

TEST_F(QueueTest, Enqueue) {
  for (int i = 0; i < 16; ++i) queue->Enqueue(q, i);

  EXPECT_EQ(16, queue->UsedSize(q));
  EXPECT_EQ(16, queue->AvailableSize(q));
}

TEST_F(QueueTest, Dequeue) {
  for (int i = 0; i < 16; ++i) queue->Enqueue(q, i);

  for (int i = 0; i < 8; ++i)
    EXPECT_EQ(i, queue->Dequeue(q)) << "Failure at index " << i;

  EXPECT_EQ(8, queue->UsedSize(q));
  EXPECT_EQ(24, queue->AvailableSize(q));
}

TEST_F(QueueTest, EnqueueMoreThanAvailableSize) {
  for (int i = 0; i < 33; ++i) queue->Enqueue(q, i);

  EXPECT_EQ(32, queue->UsedSize(q));
  EXPECT_EQ(0, queue->AvailableSize(q));
  for (int i = 0; i < 32; ++i)
    EXPECT_EQ(i, queue->Dequeue(q)) << "Failure at index " << i;
}

TEST_F(QueueTest, DequeueMoreThanUsedSize) {
  for (int i = 0; i < 16; ++i) queue->Enqueue(q, i);
  for (int i = 0; i < 16; ++i) queue->Dequeue(q);

  EXPECT_EQ(0, queue->Dequeue(q));
  AssertInitialCondition();
}

TEST_F(QueueTest, WrapAround) {
  for (int i = 0; i < 24; ++i) queue->Enqueue(q, i);
  for (int i = 0; i < 16; ++i) queue->Dequeue(q);
  for (int i = 24; i < 48; ++i) queue->Enqueue(q, i);

  for (int i = 0; i < 20; ++i)
    EXPECT_EQ(16 + i, queue->Dequeue(q)) << "Failure at index " << i;
  EXPECT_EQ(12, queue->UsedSize(q));
  EXPECT_EQ(20, queue->AvailableSize(q));
}

TEST_F(QueueTest, Add) {
  uint8_t input[16];
  for (int i = 0; i < sizeof(input); ++i) input[i] = i;

  queue->Add(q, sizeof(input), input);

  EXPECT_EQ(16, queue->UsedSize(q));
  EXPECT_EQ(16, queue->AvailableSize(q));
}

TEST_F(QueueTest, AddMoreThanAvailableSize) {
  uint8_t input[33];
  for (int i = 0; i < sizeof(input); ++i) input[i] = i;

  queue->Add(q, sizeof(input), input);

  EXPECT_EQ(32, queue->UsedSize(q));
  EXPECT_EQ(0, queue->AvailableSize(q));
  for (int i = 0; i < 32; ++i)
    EXPECT_EQ(i, queue->Dequeue(q)) << "Failure at index " << i;
}

TEST_F(QueueTest, Pop) {
  for (int i = 0; i < 24; ++i) queue->Enqueue(q, i);
  uint8_t output[9] = {0};

  queue->Pop(q, 8, output);

  for (int i = 0; i < 8; ++i)
    EXPECT_EQ(i, output[i]) << "Failure at index " << i;
  EXPECT_EQ(0, output[8]);
  EXPECT_EQ(16, queue->UsedSize(q));
  EXPECT_EQ(16, queue->AvailableSize(q));
}

TEST_F(QueueTest, PopMoreThanUsedSize) {
  for (int i = 0; i < 24; ++i) queue->Enqueue(q, i);
  uint8_t output[25] = {0};
  output[24] = 0xFF;

  queue->Pop(q, sizeof(output), output);

  for (int i = 0; i < 24; ++i)
    EXPECT_EQ(i, output[i]) << "Failure at index " << i;
  EXPECT_EQ(0xFF, output[24]);
  EXPECT_EQ(0, queue->UsedSize(q));
  EXPECT_EQ(32, queue->AvailableSize(q));
}

TEST_F(QueueTest, Clear) {
  for (int i = 0; i < 32; ++i) queue->Enqueue(q, i);

  queue->Clear(q);

  EXPECT_EQ(0, queue->UsedSize(q));
  EXPECT_EQ(32, queue->AvailableSize(q));
}

TEST_F(QueueTest, UseAfterClear) {
  uint8_t input[16] = {0};
  queue->Add(q, sizeof(input), input);
  queue->Clear(q);

  queue->Add(q, sizeof(input), input);
  queue->Dequeue(q);

  EXPECT_EQ(15, queue->UsedSize(q));
  EXPECT_EQ(17, queue->AvailableSize(q));
}

TEST_F(QueueTest, SampleTransaction) {
  uint8_t input[40];
  for (int i = 0; i < sizeof(input); ++i) input[i] = i;
  uint8_t output[40] = {0};

  queue->Add(q, 8, input);
  for (int i = 0; i < 4; ++i) queue->Dequeue(q);
  for (int i = 0; i < 24; ++i) queue->Enqueue(q, i);
  queue->Add(q, 8, input);
  queue->Clear(q);
  for (int i = 0; i < 4; ++i) queue->Enqueue(q, i);
  queue->Pop(q, 8, output);
  queue->Add(q, 40, input);
  for (int i = 0; i < 50; ++i) queue->Dequeue(q);
  queue->Add(q, 16, input);
  for (int i = 16; i < 28; ++i) queue->Enqueue(q, i);
  queue->Pop(q, 9, output);

  EXPECT_EQ(19, queue->UsedSize(q));
  EXPECT_EQ(13, queue->AvailableSize(q));
  for (int i = 0; i < 9; ++i)
    EXPECT_EQ(i, output[i]) << "Failure at index " << i;
  for (int i = 9; i < 28; ++i)
    EXPECT_EQ(i, queue->Dequeue(q)) << "Failure at index " << i;
  AssertInitialCondition();
}

TEST_F(QueueTest, CallMethodWithNullInstance) {
  int data;
  queue->Delete(NULL);
  queue->Enqueue(NULL, 0);
  EXPECT_EQ(0, queue->Dequeue(NULL));
  queue->Add(NULL, sizeof(data), &data);
  queue->Pop(NULL, sizeof(data), &data);
  queue->Clear(NULL);
  EXPECT_EQ(0, queue->UsedSize(NULL));
  EXPECT_EQ(0, queue->AvailableSize(NULL));

  SUCCEED();
}

TEST_F(QueueTest, CallMethodWithNullData) {
  queue->Add(q, 16, NULL);
  queue->Pop(q, 16, NULL);

  AssertInitialCondition();
}
