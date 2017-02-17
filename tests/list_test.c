/**
 * Copyright (C) 2017-present Jung-Sang Ahn <jungsang.ahn@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

typedef struct {
    struct list_elem elm;
    int value;
} int_node;

void destroy_int_list(struct list *int_list)
{
    int_node *node = NULL;
    struct list_elem *cursor = list_begin(int_list);
    while (cursor) {
        node = _get_entry(cursor, int_node, elm);
        cursor = list_remove(int_list, cursor);
        free(node);
    }
}

void list_validation(struct list *int_list, int *arr, size_t arr_size)
{
    size_t count = 0;
    int_node *node = NULL;
    struct list_elem *cursor = list_begin(int_list);
    while (cursor) {
        node = _get_entry(cursor, int_node, elm);
        assert(count < arr_size);
        assert(node->value == arr[count++]);
        cursor = list_next(cursor);
    }
    assert(count == arr_size);
}

void push_front_test()
{
    int i;
    int n=5;
    struct list int_list;
    int_node *node;

    list_init(&int_list);

    for (i=0; i<n; ++i) {
        node = (int_node*)malloc(sizeof(int_node));
        node->value = i * 10;
        list_push_front(&int_list, &node->elm);
    }

    {
        int arr_expected[] = {40, 30, 20, 10, 0};
        list_validation(&int_list, arr_expected, 5);
    }

    destroy_int_list(&int_list);
}

void push_back_test()
{
    int i;
    int n=5;
    struct list int_list;
    int_node *node;

    list_init(&int_list);

    for (i=0; i<n; ++i) {
        node = (int_node*)malloc(sizeof(int_node));
        node->value = i * 10;
        list_push_back(&int_list, &node->elm);
    }

    {
        int arr_expected[] = {0, 10, 20, 30, 40};
        list_validation(&int_list, arr_expected, 5);
    }

    destroy_int_list(&int_list);
}

void insert_before_test()
{
    int i;
    int n=5;
    struct list int_list;
    int_node *node;

    list_init(&int_list);

    for (i=0; i<n; ++i) {
        node = (int_node*)malloc(sizeof(int_node));
        node->value = i * 10;
        list_push_front(&int_list, &node->elm);
    }

    int_node *node_new;
    struct list_elem *cursor = list_begin(&int_list);
    while (cursor) {
        node = _get_entry(cursor, int_node, elm);
        cursor = list_next(cursor);

        node_new = (int_node*)malloc(sizeof(int_node));
        node_new->value = node->value + 5;
        list_insert_before(&int_list, &node->elm, &node_new->elm);
    }

    {
        int arr_expected[] = {45, 40, 35, 30, 25, 20, 15, 10, 5, 0};
        list_validation(&int_list, arr_expected, 10);
    }

    destroy_int_list(&int_list);
}

void insert_after_test()
{
    int i;
    int n=5;
    struct list int_list;
    int_node *node;

    list_init(&int_list);

    for (i=0; i<n; ++i) {
        node = (int_node*)malloc(sizeof(int_node));
        node->value = i * 10;
        list_push_back(&int_list, &node->elm);
    }

    int_node *node_new;
    struct list_elem *cursor = list_end(&int_list);
    while (cursor) {
        node = _get_entry(cursor, int_node, elm);
        cursor = list_prev(cursor);

        node_new = (int_node*)malloc(sizeof(int_node));
        node_new->value = node->value + 5;
        list_insert_after(&int_list, &node->elm, &node_new->elm);
    }

    {
        int arr_expected[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45};
        list_validation(&int_list, arr_expected, 10);
    }

    destroy_int_list(&int_list);
}

void pop_front_test()
{
    int i;
    int n=5;
    struct list int_list;
    int_node *node;

    list_init(&int_list);

    for (i=0; i<n; ++i) {
        node = (int_node*)malloc(sizeof(int_node));
        node->value = i * 10;
        list_push_back(&int_list, &node->elm);
    }

    struct list_elem *cursor;
    for (i=0; i<n; ++i) {
        cursor = list_pop_front(&int_list);
        assert(cursor);
        node = _get_entry(cursor, int_node, elm);
        assert(node->value == i * 10);
    }
    assert(list_is_empty(&int_list));

    destroy_int_list(&int_list);
}

void pop_back_test()
{
    int i;
    int n=5;
    struct list int_list;
    int_node *node;

    list_init(&int_list);

    for (i=0; i<n; ++i) {
        node = (int_node*)malloc(sizeof(int_node));
        node->value = i * 10;
        list_push_front(&int_list, &node->elm);
    }

    struct list_elem *cursor;
    for (i=0; i<n; ++i) {
        cursor = list_pop_back(&int_list);
        assert(cursor);
        node = _get_entry(cursor, int_node, elm);
        assert(node->value == i * 10);
    }
    assert(list_is_empty(&int_list));

    destroy_int_list(&int_list);
}

void remove_reverse_test()
{
    int i;
    int n=5;
    struct list int_list;
    int_node *node;

    list_init(&int_list);

    for (i=0; i<n; ++i) {
        node = (int_node*)malloc(sizeof(int_node));
        node->value = i * 10;
        list_push_front(&int_list, &node->elm);
    }

    struct list_elem *cursor = list_end(&int_list);
    while (cursor) {
        node = _get_entry(cursor, int_node, elm);
        cursor = list_remove_reverse(&int_list, cursor);
    }
    assert(list_is_empty(&int_list));

    destroy_int_list(&int_list);
}

int main() {
    push_front_test();
    push_back_test();
    insert_before_test();
    insert_after_test();
    pop_front_test();
    pop_back_test();
    remove_reverse_test();
    return 0;
}

