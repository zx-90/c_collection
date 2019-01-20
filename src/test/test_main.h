/*
 * Copyright (c) 2018, Evgenii Zaitcev <zx_90@mail.ru>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef ZX_TEST_MAIN_H
#define ZX_TEST_MAIN_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct zx_test_list {
    void (*func)(_Bool *result);
    char *desc;
    struct zx_test_list *next;
};

struct zx_test_list *zx_tests = NULL;

void *
zx_test_register(void (*f)(_Bool *test_result), char *desc)
{
    struct zx_test_list *old = zx_tests;
    zx_tests = malloc(sizeof(struct zx_test_list));
    zx_tests->func = f;
    zx_tests->desc = desc;
    zx_tests->next = old;
}

#include "ansi_color/ansi_color.h"

int
zx_test_all(void)
{
    struct zx_test_list *list = zx_tests;
    int ok = 0;
    int err = 0;
    while (list != NULL) {
        _Bool test_result = 0;
        printf("%s\n", list->desc);
        list->func(&test_result);
        if (test_result != 0) {
            printf(ZX_ANSI_COLOR_GREEN "OK\n" ZX_ANSI_COLOR_RESET);
            ok++;
        } else {
            printf(ZX_ANSI_COLOR_RED "ERROR!!!\n" ZX_ANSI_COLOR_RESET);
            err++;
        }
        list = list->next;
    }
    printf("\n");
    printf("TOTAL\n");
    printf("OK : " ZX_ANSI_COLOR_GREEN "%d\n" ZX_ANSI_COLOR_RESET, ok);
    printf("ERROR: ");
    if (err == 0) {
        printf("%d\n", err);
    } else {
        printf(ZX_ANSI_COLOR_RED "%d\n" ZX_ANSI_COLOR_RESET, err);
    }
    return err;
}

#endif // ZX_TEST_MAIN_H
