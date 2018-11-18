/*
 * Copyright (c) 2018, Evgenii Zaitcev <zx_90@mail.ru>
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
*/

// Capital prefix: TEST, ANSI_STRING
// Small prefix: test, ansi_string

#ifndef TEST_MAIN_H
#define TEST_MAIN_H

#ifdef TEST_MAIN

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct test_list {
    void (*func)(_Bool *result);
    char *desc;
    struct test_list *next;
};

struct test_list *tests = NULL;

void *
test_register(void (*f)(_Bool *test_result), char *desc)
{
    struct test_list *old = tests;
    tests = malloc(sizeof(struct test_list));
    tests->func = f;
    tests->desc = desc;
    tests->next = old;
}

#include "ansi_color/ansi_color.h"

int
test_all(void)
{
    struct test_list *list = tests;
    int ok = 0;
    int err = 0;
    while (list != NULL) {
        _Bool test_result = 0;
        printf("%s\n", list->desc);
        list->func(&test_result);
        if (test_result != 0) {
            printf(ANSI_COLOR_GREEN "OK\n" ANSI_COLOR_RESET);
            ok++;
        } else {
            printf(ANSI_COLOR_RED "ERROR!!!\n" ANSI_COLOR_RESET);
            err++;
        }
        list = list->next;
    }
    printf("\n");
    printf("TOTAL\n");
    printf("OK : " ANSI_COLOR_GREEN "%d\n" ANSI_COLOR_RESET, ok);
    printf("ERROR: ");
    if (err == 0) {
        printf("%d\n", err);
    } else {
        printf(ANSI_COLOR_RED "%d\n" ANSI_COLOR_RESET, err);
    }
    return err;
}

int main(void)
{
    return test_all();
}

#endif // TEST_MAIN

#endif // TEST_MAIN_H
