#pragma once

#include "util.h"

size_t b8tobase64_malloc_size(size_t s);
void b8tobase64(b8 *a, size_t in_size, char *out);
size_t base64tob8_malloc_size(char *a);
void base64tob8(char *a, b8 *out);