﻿// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "list.h"
}

namespace {
int Compare(const void* x, const void* y) {
  const int* a = (const int*)x;
  const int* b = (const int*)y;
  return *a - *b;
}
const ComparerInterfaceStruct kComparer = {Compare};

void* last_deleted_item;
int deletion_count;
void Delete(void** self) {
  last_deleted_item = *self;
  deletion_count++;
}
const DeleterInterfaceStruct kDeleter = {Delete};

const int kNumOfItems = 16;
}  // namespace

class ListTest : public ::testing::Test {
 protected:
  int items[kNumOfItems];
  List l;
  virtual void SetUp() {
    deletion_count = 0;
    last_deleted_item = NULL;
    for (int i = 0; i < kNumOfItems; ++i) items[i] = i;
    l = list->New();
    list->SetItemComparer(l, &kComparer);
    list->SetItemDeleter(l, &kDeleter);
  }
  virtual void TearDown() { list->Delete(&l); }
  void AssertInitialCondition() {
    ASSERT_TRUE(l != NULL);
    EXPECT_EQ(0, list->Count(l));
    EXPECT_EQ(NULL, list->Get(l, 0));
  }
  void AddAllItems(void) {
    for (int i = 0; i < kNumOfItems; ++i) list->Add(l, &items[i]);
  }
};

TEST_F(ListTest, ConditionAfterNew) { AssertInitialCondition(); }

TEST_F(ListTest, AddItems) {
  AddAllItems();

  EXPECT_EQ(kNumOfItems, list->Count(l));
  for (int i = 0; i < kNumOfItems; ++i)
    EXPECT_EQ(&items[i], list->Get(l, i)) << "Failure at index " << i;
  EXPECT_EQ(NULL, list->Get(l, kNumOfItems));
}

TEST_F(ListTest, FindItems) {
  AddAllItems();

  for (int i = 0; i < kNumOfItems; ++i)
    EXPECT_EQ(&items[i], list->Find(l, &i)) << "Failure at index " << i;
  int non_existed = kNumOfItems;
  EXPECT_EQ(NULL, list->Find(l, &non_existed));
}

TEST_F(ListTest, PopItems) {
  AddAllItems();

  for (int i = 0; i < kNumOfItems; ++i)
    EXPECT_EQ(&items[i], list->Pop(l, 0)) << "Failure at index " << i;
  EXPECT_EQ(NULL, list->Pop(l, 0));
  AssertInitialCondition();
}

TEST_F(ListTest, PopItemsRandomly) {
  AddAllItems();

  EXPECT_EQ(&items[kNumOfItems - 1], list->Pop(l, kNumOfItems - 1));
  EXPECT_EQ(&items[6], list->Pop(l, 6));
  EXPECT_EQ(&items[7], list->Pop(l, 6));
  EXPECT_EQ(&items[8], list->Pop(l, 6));
  EXPECT_EQ(&items[kNumOfItems - 2], list->Pop(l, kNumOfItems - 5));
  EXPECT_EQ(kNumOfItems - 5, list->Count(l));
}

TEST_F(ListTest, ClearItems) {
  AddAllItems();

  list->Clear(l);

  AssertInitialCondition();
}

TEST_F(ListTest, DeleteItems) {
  AddAllItems();

  list->Delete(&l);

  EXPECT_EQ(kNumOfItems, deletion_count);
  EXPECT_EQ(&items[kNumOfItems - 1], last_deleted_item);
  EXPECT_EQ(0, list->Count(l));
  EXPECT_EQ(NULL, list->Get(l, 0));
}

TEST_F(ListTest, SampleTransaction) {
  AddAllItems();

  EXPECT_EQ(&items[2], list->Pop(l, 2));
  EXPECT_EQ(&items[0], list->Pop(l, 0));
  EXPECT_EQ(&items[1], list->Pop(l, 0));
  EXPECT_EQ(&items[8], list->Pop(l, 5));
  list->Add(l, &items[1]);
  EXPECT_EQ(&items[9], list->Pop(l, 5));
  list->Add(l, &items[8]);
  list->Add(l, &items[10]);
  EXPECT_EQ(&items[10], list->Pop(l, 13));

  EXPECT_EQ(13, list->Count(l));
  EXPECT_EQ(&items[3], list->Get(l, 0));
  EXPECT_EQ(&items[8], list->Get(l, 12));

  list->Clear(l);

  AssertInitialCondition();
  EXPECT_EQ(13, deletion_count);
  EXPECT_EQ(&items[8], last_deleted_item);

  AddAllItems();

  EXPECT_EQ(kNumOfItems, list->Count(l));
  for (int i = 0; i < kNumOfItems; ++i)
    EXPECT_EQ(&items[i], list->Get(l, i)) << "Failure at index " << i;
}

TEST_F(ListTest, CallMethodWithNullInstance) {
  list->Delete(NULL);
  EXPECT_EQ(0, list->Count(NULL));
  EXPECT_EQ(NULL, list->Get(NULL, 0));
  list->Add(NULL, NULL);
  list->Clear(NULL);
  EXPECT_EQ(NULL, list->Find(NULL, items));
  EXPECT_EQ(NULL, list->Pop(NULL, 0));
  list->SetItemComparer(NULL, &kComparer);
  list->SetItemDeleter(NULL, &kDeleter);

  SUCCEED();
}

TEST_F(ListTest, CallMethodWithIndexLessThanZero) {
  EXPECT_EQ(NULL, list->Get(l, -1));
  EXPECT_EQ(NULL, list->Pop(l, -243));
}

TEST_F(ListTest, FindWithNotAddedItem) {
  int match = -128;
  AddAllItems();

  EXPECT_EQ(NULL, list->Find(l, &match));
}

TEST_F(ListTest, FindIfComparatorIsNotSet) {
  ComparerInterfaceStruct cis = {NULL};
  list->SetItemComparer(l, &cis);
  AddAllItems();

  EXPECT_EQ(NULL, list->Find(l, &items[1]));
}

TEST_F(ListTest, SetItemComparatorWithNull) {
  list->SetItemComparer(l, NULL);
  AddAllItems();

  EXPECT_EQ(&items[1], list->Find(l, &items[1]));
}

TEST_F(ListTest, DeleteIfDeleterIsNotSet) {
  DeleterInterfaceStruct dis = {NULL};
  list->SetItemDeleter(l, &dis);
  AddAllItems();

  list->Delete(&l);

  EXPECT_EQ(0, deletion_count);
  EXPECT_EQ(NULL, last_deleted_item);
}

TEST_F(ListTest, SetItemDeleterWithNull) {
  list->SetItemDeleter(l, NULL);
  AddAllItems();

  list->Delete(&l);

  EXPECT_EQ(kNumOfItems, deletion_count);
  EXPECT_EQ(&items[kNumOfItems - 1], last_deleted_item);
}
