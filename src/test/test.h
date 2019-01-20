/*
 * Copyright (c) 2018, Evgenii Zaitcev <zx_90@mail.ru>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef ZX_TEST_H
#define ZX_TEST_H

#include "../base/base.h"

void *
zx_test_register(void (f)(_Bool *test_result), char *desc);

#define ZX_TEST(desc) \
static void ZX_CONCAT(zx_test_,__LINE__)(_Bool *test_result); \
static void __attribute__((constructor)) ZX_CONCAT(zx_test_constructor_,__LINE__)(void) \
{ \
zx_test_register(ZX_CONCAT(&zx_test_,__LINE__), #desc); \
} \
static void ZX_CONCAT(zx_test_,__LINE__)(_Bool *test_result)

#define ZX_TEST_FAIL ; *test_result = 0; return;
#define ZX_TEST_SUCCESS ; *test_result = 1; return;
#define ZX_TEST_ASSERT(x) ; *test_result = (x);

#endif // ZX_TEST_H
