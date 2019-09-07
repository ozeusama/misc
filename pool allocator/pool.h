#pragma once

#include "util.h"

typedef struct _pool {
    size_t elem_size;
    size_t num_elems;
    size_t cur_idx;
    size_t last_idx;
    void *a;
} pool;

pool pool_init(size_t num_elems, size_t elem_size);
void *pool_malloc(pool *p);
void pool_free(pool *p, void *elem);
void pool_delete(pool *p);