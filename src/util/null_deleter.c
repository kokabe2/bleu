// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "null_deleter.h"

static void Delete(void** x) {}

static const DeleterInterfaceStruct kTheInterface = {
    .Delete = Delete,
};

const DeleterInterface NullDeleter = &kTheInterface;
