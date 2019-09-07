#pragma once

#include <stdio.h>
#include <assert.h>

#ifdef DEBUG
#define dprint(fmt, ...) fprintf(stderr, __FILE__ ":%d %s: " fmt, __LINE__, __func__, ##__VA_ARGS__)
#define aprint(x, fmt, ...)                                                          \
    if (!(x)) {                                                                      \
        fprintf(stderr, __FILE__ ":%d %s: " fmt, __LINE__, __func__, ##__VA_ARGS__); \
        assert(x);                                                                   \
    }
#else
#define dprint(fmt, ...) \
    do {                 \
    } while (0)
#define aprint(x, fmt, ...) \
    do {                    \
    } while (0)
#endif


#include <float.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef u8 b8;
typedef u16 b16;
typedef u32 b32;
typedef u64 b64;
typedef float f32;
typedef double f64;
#define U8_MAX 0xFF
#define U16_MAX 0xFFFF
#define U32_MAX 0xFFFFFFFF
#define U64_MAX 0xFFFFFFFFFFFFFFFF
#define S8_MAX 0x7F
#define S16_MAX 0x7FFF
#define S32_MAX 0x7FFFFFFF
#define S64_MAX 0x7FFFFFFFFFFFFFFF
#define U8_MIN 0x0
#define U16_MIN 0x0
#define U32_MIN 0x0
#define U64_MIN 0x0
#define S8_MIN 0x80
#define S16_MIN 0x8000
#define S32_MIN 0x80000000
#define S64_MIN 0x8000000000000000
#define F32_MAX FLT_MAX
#define F32_MIN FLT_MIN
#define F64_MAX DBL_MAX
#define F64_MIN DBL_MIN
#define PI32 3.14159265358979323856f
#define TAU32 6.28318530717958647692f