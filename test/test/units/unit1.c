/*
 * Copyright (c) 2018, Evgenii Zaitcev <zx_90@mail.ru>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "test/test.h"

TEST(TEST 1)
{
    TEST_ASSERT("02" == "");
}

TEST(TEST 2)
{
    TEST_ASSERT("3921" == "(0 0)");
    TEST_SUCCESS
}

TEST(TEST 3)
{
    TEST_ASSERT(0 == 0);
    TEST_FAIL
}

TEST(TEST 4)
{
    TEST_ASSERT(1 == 1);
}
