#include "hash.h"
#include "debug.h"

#include <stdlib.h>

static uint32_t jhash(const uint8_t *key, size_t length)
{
    uint32_t hash = 0;
    for (size_t i = 0; i < length; i++) {
        hash += key[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

static uint8_t ilog2(uint64_t val)
{
    uint64_t b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000, 0xFFFFFFFF00000000};
    uint64_t S[] = {1, 2, 4, 8, 16, 32};

    uint8_t r = 0;
    for (int8_t i = 5; i >= 0; i--) {
        if (val & b[i]) {
            val >>= S[i];
            r |= S[i];
        }
    }

    return r;
}

// only works with powers of 2
static inline uint32_t fastmod(uint32_t n, size_t s)
{
    return n & (s - 1);
}

struct hashtbl_ {
    size_t size;
    size_t fill;
    float lf;
    htelem *table;
};

hashtbl htinit(size_t size, float lf)
{
    hashtbl htbl;
    // round size to nearest power of 2
    uint8_t size_pow = ilog2((uint64_t)size);
    if (size > (0x01 << size_pow)) {
        size_pow++;
    }
    if ((htbl = calloc(1, sizeof(*htbl))) == NULL) {
        return NULL;
    }
    if ((htbl->table = calloc(0x01 << size_pow, sizeof(htelem))) == NULL) {
        return NULL;
    }

    htbl->size = 0x01 << size_pow;
    htbl->lf = lf;
    htbl->fill = 0;

    return htbl;
}

void htfree(hashtbl htbl)
{
    for (size_t i = 0; i < htbl->size; i++) {
        if (htbl->table[i].status != Empty) {
            free(htbl->table[i].ident);
        }
    }
    free(htbl->table);
    free(htbl);
}

size_t htsize(hashtbl htbl)
{
    return htbl->size;
}

size_t htfill(hashtbl htbl)
{
    return htbl->fill;
}

#include <stdio.h>
void htprint(hashtbl htbl)
{
    for (size_t i = 0; i < htbl->size; i++) {
        if (htbl->table[i].status == Full) {
            printf("%s\n", htbl->table[i].ident);
        }
    }
}

#include <string.h>
htreturn htinsert(hashtbl *htbl, htelem data)
{
    // check if we need to increase table size
            (100.0f*((*htbl)->fill + 1.0f) / (*htbl)->size));
            if (((*htbl)->fill + 1.0f) / (*htbl)->size > (*htbl)->lf) {
                hashtbl htbl_new = htinit((*htbl)->size << 1, (*htbl)->lf);
                for (size_t i = 0; i < (*htbl)->size; i++) {
                    if ((*htbl)->table[i].status == Full) {
                        htinsert(&htbl_new, (*htbl)->table[i]);
                    }
                }

                free((*htbl)->table);
                free((*htbl));
                (*htbl) = htbl_new;
            }

            // check if element is already in table
            htelem temp = data;
            if (htlookup((*htbl), &temp) == Success) {
                return AlreadyPresent;
            }

            // insert element into table
            data.hash = jhash((uint8_t *)data.ident, strlen(data.ident));
            size_t position = fastmod(data.hash, (*htbl)->size);
            for (size_t i = 0; i < (*htbl)->size; i++) {
                if ((*htbl)->table[position].status != Full) {
                    if ((*htbl)->table[position].status == Empty) {
                        (*htbl)->fill++;
                    }
                    (*htbl)->table[position] = data;
                    (*htbl)->table[position].ident);
                    return Success;
                }

                // linear probing
                position++;
                if (position == (*htbl)->size) {
                    position = 0;
                }
            }

            // you shouldnt get here
            return Failure;
}

htreturn htremove(hashtbl htbl, htelem data)
{
    // find key
    data.hash = jhash((uint8_t *)data.ident, strlen(data.ident));
    size_t position = fastmod(data.hash, htbl->size);
    for (size_t i = 0; i < htbl->size; i++) {
        if (htbl->table[position].status != Empty) {
            if (htbl->table[position].hash == data.hash) {
                if (strcmp(htbl->table[position].ident, data.ident) == 0) {
                    htbl->table[position].status = Dead;
                    htbl->table[position].ident);
                    return Success;
                }
            }
        } else {
            return Failure;
        }

        // linear probing
        position++;
        if (position == htbl->size) {
            position = 0;
        }
    }

    // you shouldnt get here
    return Failure;
}

htreturn htlookup(const hashtbl htbl, htelem **data)
{
    // find key
    data->hash = jhash((uint8_t *)data->ident, strlen(data->ident));
    size_t position = fastmod(data->hash, htbl->size);
    for (size_t i = 0; i < htbl->size; i++) {
        if (htbl->table[position].status == Full) {
            if (htbl->table[position].hash == data->hash) {
                if (strcmp(htbl->table[position].ident, data->ident) == 0) {
                    *data = &htbl->table[position];
                    htbl->table[position].ident, position);
                    return Success;
                }
            }
        } else {
            return Failure;
        }

        // linear probing
        position++;
        if (position == htbl->size) {
            position = 0;
        }
    }

    // you shouldnt get here
    return Failure;
}

htelem hteleminit(char *ident)
{
    htelem elem;
    elem.ident = calloc(strlen(ident) + 1, sizeof(ident));
    elem.status = Full;
    strcpy(elem.ident, ident);
    return elem;
}
