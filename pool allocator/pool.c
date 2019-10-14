#include "pool.h"

#include "stdlib.h"

typedef union _pool_elem {
    void *a;
    union _pool_elem *next;
} pool_elem;

#include <stdio.h>
pool pool_init(size_t num_elems, size_t elem_size)
{
    pool p = {.elem_size = elem_size,
              .num_elems = num_elems,
              .cur_idx = 0,
              .last_idx = num_elems - 1,
              .a = calloc(num_elems, elem_size)};
    // last element doesnt have a next pointer
    for (size_t i = 0; i < num_elems - 1; i++) {
        ((pool_elem *)(p.a + elem_size * i))->next = (pool_elem *)(p.a + elem_size * (i + 1));
    }
    return p;
}

void *pool_malloc(pool *p)
{
    void *ret = p->a + p->elem_size * p->cur_idx;
    void *next = ((pool_elem *)ret)->next;
    p->cur_idx = (next - p->a) / p->elem_size;
    return ret;
}

void pool_free(pool *p, void *elem)
{
    ((pool_elem *)(p->a + p->elem_size * p->last_idx))->next = elem;
    p->last_idx = (elem - p->a) / p->elem_size;
}

void pool_delete(pool *p)
{
    free(p->a);
}
