#include "pool.h"
#include "util.h"

void pool_test();

int main()
{
    pool_test();
    return 0;
}

typedef union _vec3 {
    struct {
        f32 r, g, b;
    };
    struct {
        f32 x, y, z;
    };
    f32 d[3];
} vec3;

typedef struct _data {
    vec3 col, pos;
    char name[128];
} data;

#include <stdlib.h>
#include <string.h>
#include <time.h>

void pool_test()
{
    pool p = pool_init(80, sizeof(data));
    // hack: we know the next pointer part of the pool_elem union occupies the space of the col
    // element of the data struct. because of this we can write in the name element without any
    // worry of it being overwritten when we free elements so we can see which elements have been
    // freed and which havent.
    for (size_t i = 0; i < p.num_elems; i++) {
        strcpy(((data *)p.a + i)->name, "empty");
    }

    // manip
    data *test_data[40];
    // allocates 40 structs
    for (u16 i = 0; i < 40; i++) {
        test_data[i] = pool_malloc(&p);
        strcpy(test_data[i]->name, "full");
    }

    // randomly deallocates from my array of structs and then reallocates one in its place. this
    // effectively shuffles the active structs.
    srand(time(NULL));
    for (u32 i = 0; i < 10000000; i++) {
        size_t free_idx = rand() % 40;
        strcpy(test_data[free_idx]->name, "empty");
        pool_free(&p, test_data[free_idx]);
        test_data[free_idx] = pool_malloc(&p);
        strcpy(test_data[free_idx]->name, "full");
    }

    // print results. it should look random
    printf("[");
    for (size_t i = 0; i < p.num_elems; i++) {
        if (strcmp(((data *)p.a + i)->name, "full") == 0) {
            printf("X");
        } else if (strcmp(((data *)p.a + i)->name, "empty") == 0) {
            printf(" ");
        } else {
            printf("?");
        }
    }
    printf("]\n");
}
