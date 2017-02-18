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

#pragma once

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct list_elem {
    struct list_elem *prev;
    struct list_elem *next;
};

struct list {
    struct list_elem *head;
    struct list_elem *tail;
};

#ifndef _get_entry
#define _get_entry(ELEM, STRUCT, MEMBER) \
    ((STRUCT *) ((uint8_t *) (ELEM) - offsetof (STRUCT, MEMBER)))
#endif

static inline void list_init(struct list *list)
{
    list->head = NULL;
    list->tail = NULL;
}

void list_push_front(struct list *list, struct list_elem *e);
void list_push_back(struct list *list, struct list_elem *e);

// insert 'e' before 'pivot'
void list_insert_before(struct list *list, struct list_elem *pivot, struct list_elem *e);

// insert 'e' after 'pivot'
void list_insert_after(struct list *list, struct list_elem *pivot, struct list_elem *e);

struct list_elem *list_remove(struct list *list, struct list_elem *e);
struct list_elem *list_remove_reverse(struct list *list, struct list_elem *e);

struct list_elem *list_pop_front(struct list *list);
struct list_elem *list_pop_back(struct list *list);

static inline struct list_elem *list_begin(struct list *list)
{
    return list->head;
}

static inline struct list_elem *list_end(struct list *list)
{
    return list->tail;
}

static inline struct list_elem *list_next(struct list_elem *e)
{
    return e->next;
}

static inline struct list_elem *list_prev(struct list_elem *e)
{
    return e->prev;
}

static inline int list_is_empty(struct list *list)
{
    return list->head == NULL;
}

#ifdef __cplusplus
}
#endif
