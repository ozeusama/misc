#include <stdint.h>

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

