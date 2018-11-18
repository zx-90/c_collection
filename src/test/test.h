/*
 * Copyright (c) 2018, Evgenii Zaitcev <zx_90@mail.ru>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

// Capital prefix: TEST
// Small prefix: test

#ifndef TEST_H
#define TEST_H

void *
test_register(void (f)(_Bool *test_result), char *desc);

#define TEST_STRING_CONCAT_INNER(x, y) x ## y
#define TEST_STRING_CONCAT(x, y) TEST_STRING_CONCAT_INNER(x, y)

#define TEST(desc)\
static void TEST_STRING_CONCAT(test_,__LINE__)(_Bool *test_result); \
static void __attribute__((constructor)) TEST_STRING_CONCAT(test_constructor_,__LINE__)(void) \
{ \
test_register(TEST_STRING_CONCAT(&test_,__LINE__), #desc); \
} \
static void TEST_STRING_CONCAT(test_,__LINE__)(_Bool *test_result)

#define TEST_FAIL ; *test_result = 0; return;
#define TEST_SUCCESS ; *test_result = 1; return;
#define TEST_ASSERT(x) ; *test_result = (x);

#endif // TEST_H
