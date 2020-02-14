#include "myutil.h"

#include <string.h>

#define TEST_HEAP_SIZE 1000
#define TEST_HEAP_SIZE_BOUNDARY 64

/** check if alllocate status OK */
#define TEST_ALLOCATOR_STATUS() do { \
        EXPECT_EQ(Allocator_capacity(alloc), capacity); \
        EXPECT_LE(Allocator_available(alloc), available - size); \
        EXPECT_LE(Allocator_available(alloc), capacity); \
        available = Allocator_available(alloc); \
    } while (false)

/** alloc a block of memory and check if allloc success */
#define TEST_ALLOC(variable, type, count) do { \
        size = sizeof(type) * count; \
        int *variable = (int *)Allocator_alloc(alloc, size); \
        EXPECT_NOT_NULL(variable); \
        memset(variable, 0, size); \
        TEST_ALLOCATOR_STATUS(); \
    } while (false)

/** check if any memory leak */
#define TEST_LEAK() do { \
        for (i = 0; i < TEST_HEAP_SIZE_BOUNDARY; i++) \
            EXPECT_EQ(bufb[i], (byte)i); \
        for (i = TEST_HEAP_SIZE + TEST_HEAP_SIZE_BOUNDARY; i < TEST_HEAP_SIZE_BOUNDARY; i++) \
            EXPECT_EQ(bufb[i], (byte)i); \
    } while (false)

TEST_CASE(static_allocator)
{
    size_t size, i;
    
    /* 4 bytes aligned. */
    uint32_t buf[(TEST_HEAP_SIZE + TEST_HEAP_SIZE_BOUNDARY * 2) / 4 + 1];
    byte *bufb = (byte *)buf;
    for (i = 0; i < TEST_HEAP_SIZE + TEST_HEAP_SIZE_BOUNDARY * 2; i++)
        bufb[i] = (byte)i;

    /* test allocate */
    Allocator *alloc = StaticAllocator(TEST_HEAP_SIZE, buf + TEST_HEAP_SIZE_BOUNDARY / 4);
    EXPECT_NOT_NULL(alloc);

    /* test capacity */
    size_t capacity = Allocator_capacity(alloc);
    EXPECT_EQ(capacity, TEST_HEAP_SIZE);

    /* test available */
    size_t available = Allocator_available(alloc);
    EXPECT_LE(available, capacity);
    EXPECT_GE(available, capacity / 10 * 9);    /* at least 90% remains */

    /* test alloc */
    TEST_ALLOC(a, int, 11);
    TEST_ALLOC(b, float, 7);

    /* test alloc failed */
    TEST_ALLOC(c, byte, available);
    int *d = (int *)Allocator_alloc(alloc, sizeof(int));
    EXPECT_NULL(d);
    TEST_ALLOCATOR_STATUS();

    /* check memory leak */
    TEST_LEAK();
}

TEST_SUITE(allocator)
{
    TEST_RUN_CASE(static_allocator);
}
