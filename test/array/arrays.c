/*
 * Copyright (c) 2018, Evgenii Zaitcev <zx_90@mail.ru>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

#include "arrays.h"

ZX_ARRAY_PVECTOR_BODY(int, dozens, 16)

static _Bool
before_free_vector(struct vector* vec)
{
    free(vec->x);
    free(vec->y);
    return 1;
}

ZX_ARRAY_PVECTOR_BODY_FREE(struct vector, vectors, 4, before_free_vector)

