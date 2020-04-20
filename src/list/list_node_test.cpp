// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "list/list_node.h"
}

class ListNodeTest : public ::testing::Test {
 protected:
  char item1[8];
  ListNode ln1;
  ListNode ln2;

  virtual void SetUp() {
    ln1 = listNode->New(item1);
    ln2 = listNode->New(NULL);
  }

  virtual void TearDown() {
    if (ln1 != NULL) listNode->Delete(&ln1);
    if (ln2 != NULL) listNode->Delete(&ln2);
  }
};

TEST_F(ListNodeTest, ConditionAfterNew) {
  EXPECT_EQ(item1, listNode->GetItem(ln1));
  EXPECT_EQ(NULL, listNode->GetNext(ln1));

  EXPECT_EQ(NULL, listNode->GetItem(ln2));
  EXPECT_EQ(NULL, listNode->GetNext(ln2));
}

TEST_F(ListNodeTest, Delete) {
  listNode->Delete(&ln1);

  EXPECT_EQ(NULL, ln1);
}

TEST_F(ListNodeTest, HowToUse) {
  char item2[2];

  listNode->SetItem(ln1, item2);
  listNode->SetNext(ln1, ln2);

  EXPECT_EQ(item2, listNode->GetItem(ln1));
  EXPECT_EQ(ln2, listNode->GetNext(ln1));
}
