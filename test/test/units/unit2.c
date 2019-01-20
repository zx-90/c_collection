/*
 * Copyright (c) 2018, Evgenii Zaitcev <zx_90@mail.ru>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "test/test.h"

ZX_TEST(TEST 1)
{
    ZX_TEST_ASSERT("02" == "");
}

ZX_TEST(TEST 2)
{
    ZX_TEST_ASSERT("3921" == "(0 0)");
}

ZX_TEST(TEST 3)
{
    ZX_TEST_ASSERT(0 == 0);
}

ZX_TEST(TEST 4)
{
    ZX_TEST_ASSERT(1 == 1);
}
