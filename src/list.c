/**
 * Copyright (C) 2013-present Jung-Sang Ahn <jungsang.ahn@gmail.com>
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

#include "list.h"

void list_push_front(struct list *list, struct list_elem *e)
{
    if (list->head == NULL) {
        list->head = e;
        list->tail = e;
        e->next = e->prev = NULL;
    } else {
        list->head->prev = e;
        e->prev = NULL;
        e->next = list->head;
        list->head = e;
    }
}

void list_push_back(struct list *list, struct list_elem *e)
{
    if (list->tail == NULL) {
        list->head = e;
        list->tail = e;
        e->next = e->prev = NULL;
    } else {
        list->tail->next = e;
        e->prev = list->tail;
        e->next = NULL;
        list->tail = e;
    }
}

void list_insert_before(struct list *list, struct list_elem *pivot, struct list_elem *e)
{
    e->prev = pivot->prev;
    e->next = pivot;
    if (pivot->prev) {
        pivot->prev->next = e;
    } else {
        list->head = e;
    }
    pivot->prev = e;
}

void list_insert_after(struct list *list, struct list_elem *pivot, struct list_elem *e)
{
    e->next = pivot->next;
    e->prev = pivot;
    if (pivot->next) {
        pivot->next->prev = e;
    } else {
        list->tail = e;
    }
    pivot->next = e;
}

struct list_elem *list_remove(struct list *list, struct list_elem *e)
{
    if (e) {
        if (e->next) e->next->prev = e->prev;
        if (e->prev) e->prev->next = e->next;

        if (list->head == e) list->head = e->next;
        if (list->tail == e) list->tail = e->prev;

        return e->next;
    }
    return NULL;
}

struct list_elem *list_remove_reverse(struct list *list, struct list_elem *e)
{
    if (e) {
        if (e->next) e->next->prev = e->prev;
        if (e->prev) e->prev->next = e->next;

        if (list->head == e) list->head = e->next;
        if (list->tail == e) list->tail = e->prev;

        return e->prev;
    }
    return NULL;
}

struct list_elem *list_pop_front(struct list *list)
{
    struct list_elem *e = list->head;
    if (e) {
        if (e->next) e->next->prev = e->prev;
        if (e->prev) e->prev->next = e->next;

        if (list->head == e) list->head = e->next;
        if (list->tail == e) list->tail = e->prev;

        return e;
    }
    return NULL;
}

struct list_elem *list_pop_back(struct list *list)
{
    struct list_elem *e = list->tail;
    if (e) {
        if (e->next) e->next->prev = e->prev;
        if (e->prev) e->prev->next = e->next;

        if (list->head == e) list->head = e->next;
        if (list->tail == e) list->tail = e->prev;

        return e;
    }
    return NULL;
}

