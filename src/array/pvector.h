/*
 * Copyright (c) 2018-2019, Evgenii Zaitcev <zx_90@mail.ru>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef ZX_ARRAY_PVECTOR_H
#define ZX_ARRAY_PVECTOR_H

#include <stddef.h>
#include <stdlib.h>
#include "../base/base.h"



#define ZX_ARRAY_PVECTOR_STRUCT(type, prefix) \
struct ZX_CONCAT(prefix,_array) { \
    size_t size; \
    size_t capacity; \
    type** data; \
};



#define ZX_ARRAY_PVECTOR_HEADER(type, prefix) \
_Bool \
ZX_CONCAT(prefix,_init_with)(struct ZX_CONCAT(prefix,_array) *array, size_t start_capacity); \
 \
_Bool \
ZX_CONCAT(prefix,_init)(struct ZX_CONCAT(prefix,_array) *array); \
 \
_Bool \
ZX_CONCAT(prefix,_free)(struct ZX_CONCAT(prefix,_array) *array); \
 \
_Bool \
ZX_CONCAT(prefix,_realloc_array)(struct ZX_CONCAT(prefix,_array) *array); \
 \
_Bool \
ZX_CONCAT(prefix,_push)(struct ZX_CONCAT(prefix,_array) *array, type* value); \
 \
type* \
ZX_CONCAT(prefix,_pop)(struct ZX_CONCAT(prefix,_array) *array, type* value); \
 \
_Bool \
ZX_CONCAT(prefix,_popd)(struct ZX_CONCAT(prefix,_array) *array, type* value); \
 \
type* \
ZX_CONCAT(prefix,_get)(struct ZX_CONCAT(prefix,_array) *array, size_t index); \
 \
_Bool \
ZX_CONCAT(prefix,_set)(struct ZX_CONCAT(prefix,_array) *array, size_t index, type* value); \
 \
type* \
ZX_CONCAT(prefix,_change_to)(struct ZX_CONCAT(prefix,_array) *array, size_t index, type* new_value); \
 \
_Bool \
ZX_CONCAT(prefix,_swap)(struct ZX_CONCAT(prefix,_array) *array, size_t index1, size_t index2); \
 \
_Bool \
ZX_CONCAT(prefix,_insert)(struct ZX_CONCAT(prefix,_array) *array, size_t index, type* value); \
 \
type* \
ZX_CONCAT(prefix,_tear)(struct ZX_CONCAT(prefix,_array) *array, size_t index); \
 \
_Bool \
ZX_CONCAT(prefix,_delete)(struct ZX_CONCAT(prefix,_array) *array, size_t index); \



#define ZX_ARRAY_PVECTOR_BODY_FREE(type, prefix, min, before_free_func) \
static inline _Bool \
ZX_CONCAT(prefix,_double_capacity_if_full)(struct ZX_CONCAT(prefix,_array) *array) \
{ \
    if (array->size < array->capacity) { \
        return 1; \
    } \
    array->capacity *= 2; \
    type** new_array = realloc(array->data, sizeof(type*) * array->capacity); \
    if (new_array == NULL) { \
        return 0; \
    } \
    array->data = new_array; \
    return 1; \
} \
 \
_Bool \
ZX_CONCAT(prefix,_init_with)(struct ZX_CONCAT(prefix,_array) *array, size_t start_capacity) \
{ \
    array->size = 0; \
    array->capacity = start_capacity; \
    array->data = malloc(sizeof(type*) * array->capacity); \
    return array->data != NULL; \
} \
 \
_Bool \
ZX_CONCAT(prefix,_init)(struct ZX_CONCAT(prefix,_array) *array) \
{ \
    return ZX_CONCAT(prefix,_init_with)(array, min); \
} \
 \
_Bool \
ZX_CONCAT(prefix,_free)(struct ZX_CONCAT(prefix,_array) *array) \
{ \
    _Bool result = 1; \
    for (size_t i = 0; i < array->size; i++) { \
        result = before_free_func(array->data[i]) && result; \
        free(array->data[i]); \
    } \
    free(array->data); \
    return result; \
} \
 \
_Bool \
ZX_CONCAT(prefix,_realloc_array)(struct ZX_CONCAT(prefix,_array) *array) \
{ \
    if (array->capacity <= min) { \
        return 1; \
    } \
    array->capacity = min; \
    while (array->capacity < array->size) array->capacity *= 2; \
    type** new_array = realloc(array->data, sizeof(type*) * array->capacity); \
    if (new_array == NULL) { \
        return 0; \
    } \
    array->data = new_array; \
    return 1; \
} \
 \
_Bool \
ZX_CONCAT(prefix,_push)(struct ZX_CONCAT(prefix,_array) *array, type* value) \
{ \
    if (!ZX_CONCAT(prefix,_double_capacity_if_full)(array)) { \
        return 0; \
    } \
    array->data[array->size++] = value; \
    return 1; \
} \
 \
type* \
ZX_CONCAT(prefix,_pop)(struct ZX_CONCAT(prefix,_array) *array, type* value) \
{ \
    return array->data[--array->size]; \
} \
 \
_Bool \
ZX_CONCAT(prefix,_popd)(struct ZX_CONCAT(prefix,_array) *array, type* value) \
{ \
    if (!before_free_func(array->data[array->size - 1])) { \
        return 0; \
    } \
    free(array->data[array->size - 1]); \
    array->size--; \
    return 1; \
} \
 \
type* \
ZX_CONCAT(prefix,_get)(struct ZX_CONCAT(prefix,_array) *array, size_t index) \
{ \
    if (index >= array->size) { \
        return NULL; \
    } \
    return array->data[index]; \
} \
 \
_Bool \
ZX_CONCAT(prefix,_set)(struct ZX_CONCAT(prefix,_array) *array, size_t index, type* value) \
{ \
    if (index > array->size) { \
        return 0; \
    } \
    if (index == array->size) { \
        return ZX_CONCAT(prefix,_push)(array, 0); \
    } \
    if (!before_free_func(array->data[index])) { \
        return 0; \
    } \
    free(array->data[index]); \
    array->data[index] = value; \
    return 1; \
} \
 \
type* \
ZX_CONCAT(prefix,_change_to)(struct ZX_CONCAT(prefix,_array) *array, size_t index, type* new_value) \
{ \
    if (index >= array->size) { \
        return NULL; \
    } \
    type* old_value = array->data[index]; \
    array->data[index] = new_value; \
    return old_value; \
} \
 \
_Bool \
ZX_CONCAT(prefix,_swap)(struct ZX_CONCAT(prefix,_array) *array, size_t index1, size_t index2) \
{ \
    if ((index1 >= array->size) || (index2 >= array->size)) { \
        return 0; \
    } \
    type* temp = array->data[index1]; \
    array->data[index1] = array->data[index2]; \
    array->data[index2] = temp; \
    return 1; \
} \
 \
_Bool \
ZX_CONCAT(prefix,_insert)(struct ZX_CONCAT(prefix,_array) *array, size_t index, type* value) \
{ \
    if (index > array->size) { \
        return 0; \
    } \
    if (index == array->size) { \
        return ZX_CONCAT(prefix,_push)(array, 0); \
    } \
    if (!ZX_CONCAT(prefix,_double_capacity_if_full)(array)) { \
        return 0; \
    } \
    array->size++; \
    for (size_t i = array->size - 1; i > index + 1; --i) { \
        array->data[i] = array->data[i - 1]; \
    } \
    array->data[index] = value; \
    return 1; \
} \
 \
type* \
ZX_CONCAT(prefix,_tear)(struct ZX_CONCAT(prefix,_array) *array, size_t index) \
{ \
    if (index >= array->size) { \
        return NULL; \
    } \
    type* result = array->data[index]; \
    for (size_t i = index; i < array->size - 1; ++i) { \
        array->data[index] = array->data[index + 1]; \
    } \
    array->size--; \
    return result; \
} \
 \
_Bool \
ZX_CONCAT(prefix,_delete)(struct ZX_CONCAT(prefix,_array) *array, size_t index) \
{ \
    type* element = ZX_CONCAT(prefix,_tear)(array, index); \
    if (element == NULL) { \
        return 0; \
    } \
    if (!before_free_func(element)) { \
        return 0; \
    } \
    free(element); \
    return 1; \
} \



#define ZX_ARRAY_PVECTOR_BODY(type, prefix, min) \
static inline _Bool \
ZX_CONCAT(prefix,_free_element)(type* value) \
{ \
    return 1; \
} \
 \
ZX_ARRAY_PVECTOR_BODY_FREE(type, prefix, min, ZX_CONCAT(prefix,_free_element))



#endif // ZX_ARRAY_PVECTOR_H

