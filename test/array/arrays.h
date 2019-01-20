/*
 * Copyright (c) 2018, Evgenii Zaitcev <zx_90@mail.ru>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef ARRAYS_H
#define ARRAYS_H

#include "array/pvector.h"

ZX_ARRAY_PVECTOR_STRUCT(int, dozens)
ZX_ARRAY_PVECTOR_HEADER(int, dozens)

struct vector {
    double* x;
    double* y;
};

ZX_ARRAY_PVECTOR_STRUCT(struct vector, vectors)
ZX_ARRAY_PVECTOR_HEADER(struct vector, vectors)

#endif // ARRAYS_H
