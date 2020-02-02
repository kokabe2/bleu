// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "null_xorshift_plus.h"

#include "xorshift_plus_private.h"

static uint64_t Generate(XorshiftPlus unused) { return 0; }
static const XorshiftPlusAbstractMethodStruct kTheMethod = {
    .Generate = Generate,
};
static const XorshiftPlusStruct kTheInstance = {
    .impl = &kTheMethod,
};  // Use const for .rodata section.
const XorshiftPlus kNullXorshiftPlus = (XorshiftPlus)&kTheInstance;
