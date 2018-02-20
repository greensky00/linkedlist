
#include "list.h"

#include "test_common.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    struct list_elem elm;
    int value;
} int_node;

int destroy_int_list(struct list *int_list)
{
    int_node *node = NULL;
    struct list_elem *cursor = list_begin(int_list);
    while (cursor) {
        node = _get_entry(cursor, int_node, elm);
        cursor = list_remove(int_list, cursor);
        free(node);
    }
    return 0;
}

int list_validation(struct list *int_list, int *arr, size_t arr_size)
{
    size_t count = 0;
    int_node *node = NULL;
    struct list_elem *cursor = list_begin(int_list);
    while (cursor) {
        node = _get_entry(cursor, int_node, elm);
        CHK_SM(count, arr_size);
        CHK_EQ(arr[count++], node->value);
        cursor = list_next(cursor);
    }
    CHK_EQ(arr_size, count);
    return 0;
}

int push_front_test()
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
    return 0;
}

int push_back_test()
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
    return 0;
}

int insert_before_test()
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
    return 0;
}

int insert_after_test()
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
    return 0;
}

int pop_front_test()
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
        CHK_OK(cursor);
        node = _get_entry(cursor, int_node, elm);
        CHK_EQ(i * 10, node->value);
    }
    CHK_OK(list_is_empty(&int_list));

    destroy_int_list(&int_list);
    return 0;
}

int pop_back_test()
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
        CHK_OK(cursor);
        node = _get_entry(cursor, int_node, elm);
        CHK_EQ(i * 10, node->value);
    }
    CHK_OK(list_is_empty(&int_list));

    destroy_int_list(&int_list);
    return 0;
}

int remove_reverse_test()
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
    CHK_OK(list_is_empty(&int_list));

    destroy_int_list(&int_list);
    return 0;
}

int main(int argc, char** argv) {
    TestSuite ts(argc, argv);

    ts.doTest("push front test", push_front_test);
    ts.doTest("push back test", push_back_test);
    ts.doTest("insert before test", insert_before_test);
    ts.doTest("insert after test", insert_after_test);
    ts.doTest("pop front test", pop_front_test);
    ts.doTest("pop back test", pop_back_test);
    ts.doTest("remove reverse test", remove_reverse_test);
    return 0;
}

