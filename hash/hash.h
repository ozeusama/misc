#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct hashtbl_ *hashtbl;

// initializes hash table with size 'size'
// 'lf' determines the load factor the hash table must meet before it resizes
hashtbl htinit(size_t size, float lf);
// resizes hash table
void htfree(hashtbl htbl);
// returns the size of the hash table
size_t htsize(hashtbl htbl);
// returns number of elements in the table
size_t htfill(hashtbl htbl);
// prints all elements in the hash table
void htprint(hashtbl htbl);

typedef enum elemstatus_ {
    Empty = 0, Full, Dead,
} elemstatus;

typedef struct htelem_ {
    char *ident;
    elemstatus status;
    uint32_t hash;
} htelem;

typedef enum htreturn_ {
    Success, Failure, AlreadyPresent,
} htreturn;

// inserts 'data' into 'htbl'
// returns 'AlreadyPresent' if the key is already in the table
htreturn htinsert(hashtbl *htbl, htelem data);
// removes element matching 'data' from 'htbl'
// returns 'Failure' if 'data' is not present in the table
htreturn htremove(hashtbl htbl, htelem data);
// looks up element pointed to by 'data' and redirects pointer to the location
// of the element in the table
// returns 'Failure' if the element is not found
htreturn htlookup(const hashtbl htbl, htelem **data);
// creates element for hash table
htelem hteleminit(char *ident);
