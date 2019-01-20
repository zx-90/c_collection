/*
 * Copyright (c) 2018, Evgenii Zaitcev <zx_90@mail.ru>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "test/test.h"
#include "test/test_main.h"
#include "arrays.h"

ZX_TEST(pointer vector of ints)
{
    struct dozens_array dozens;
    dozens_init(&dozens);

    ZX_TEST_ASSERT(dozens.size == 0);
    ZX_TEST_ASSERT(dozens.capacity == 16);
    ZX_TEST_ASSERT(dozens.data != NULL);

    for (size_t i = 0; i < 17; i++) {
        int *element = malloc(sizeof(int));
        *element = i * 12;
        dozens_push(&dozens, element);
    }

    ZX_TEST_ASSERT(dozens.size == 17);
    ZX_TEST_ASSERT(dozens.capacity == 32);
    ZX_TEST_ASSERT(dozens.data != NULL);

    ZX_TEST_ASSERT(dozens_get(&dozens, -1) == NULL);
    ZX_TEST_ASSERT(*dozens_get(&dozens, 0) == 0);
    ZX_TEST_ASSERT(*dozens_get(&dozens, 5) == 60);
    ZX_TEST_ASSERT(*dozens_get(&dozens, 16) == 192); // 16 * 12 = 192
    ZX_TEST_ASSERT(dozens_get(&dozens, 17) == NULL);

    dozens_free(&dozens);
}

ZX_TEST(pointer vector of structs)
{
    struct vectors_array vectors;
    vectors_init(&vectors);

    ZX_TEST_ASSERT(vectors.size == 0);
    ZX_TEST_ASSERT(vectors.capacity == 4);
    ZX_TEST_ASSERT(vectors.data != NULL);

    for (size_t i = 0; i < 5; i++) {
        struct vector* vec = malloc(sizeof(struct vector));

        double *x = malloc(sizeof(double));
        *x = 2 * i + 1;
        vec->x = x;

        double *y = malloc(sizeof(double));
        *y = 16 - 2 * i;
        vec->y = y;

        vectors_push(&vectors, vec);
    }

    ZX_TEST_ASSERT(vectors.size == 5);
    ZX_TEST_ASSERT(vectors.capacity == 8);
    ZX_TEST_ASSERT(vectors.data != NULL);

    ZX_TEST_ASSERT(vectors_get(&vectors, -1) == NULL);
    ZX_TEST_ASSERT(*vectors_get(&vectors, 0)->x == 1);
    ZX_TEST_ASSERT(*vectors_get(&vectors, 0)->y == 16);
    ZX_TEST_ASSERT(*vectors_get(&vectors, 4)->x == 9);
    ZX_TEST_ASSERT(*vectors_get(&vectors, 4)->y == 8);
    ZX_TEST_ASSERT(vectors_get(&vectors, 5) == NULL);

    vectors_free(&vectors);
}

int
main(void)
{
    return zx_test_all();
}

