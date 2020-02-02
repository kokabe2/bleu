// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "null_xorshift.h"

#include "xorshift_private.h"

static uint32_t Generate(Xorshift unused) { return 0; }
static const XorshiftAbstractMethodStruct kTheMethod = {
    .Generate = Generate,
};
static const XorshiftStruct kTheInstance = {
    .impl = &kTheMethod,
};  // Use const for .rodata section.
const Xorshift kNullXorshift = (Xorshift)&kTheInstance;
