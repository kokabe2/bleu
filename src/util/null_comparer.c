// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "null_comparer.h"

static int Compare(const void* x, const void* y) { return 0; }

static const ComparerInterfaceStruct kTheInterface = {
    .Compare = Compare,
};

const ComparerInterface NullComparer = &kTheInterface;
