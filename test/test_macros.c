#include "myutil.h"

TEST_CASE(align)
{
    EXPECT_EQ(ALIGN(0x1234567, 4), 0x1234568);
    EXPECT_EQ(ALIGN(0x1234567, 32), 0x1234580);
    EXPECT_EQ(ALIGN(1234567, 4), 1234568);
}

TEST_CASE(minmax)
{
        /* test MAX MIN */
    int i = MAX(1, 2);
    EXPECT_EQ(i, 2);
    i = MIN(1, 2);
    EXPECT_EQ(i, 1);
    i = MAX(-1, -2);
    EXPECT_EQ(i, -1);
    i = MIN(-1, -2);
    EXPECT_EQ(i, -2);
    i = MAX(1, 2, 3, 14, 5, 6);
    EXPECT_EQ(i, 14);
    i = MIN(1, 2, -3, 4, 5, 6);
    EXPECT_EQ(i, -3);

    i = MIN(0, 0, 0, 0, 0, 0);
    EXPECT_EQ(i, 0);
    i = MAX(0, 0, 0, 0, 0, 0);
    EXPECT_EQ(i, 0);

    float f = MIN(0xab, 2.3, -1.5, 4);
    EXPECT_EQ_F(f, -1.5);

#define TEST_COUNT 1000
    int as[TEST_COUNT];
    for (i = 0; i < TEST_COUNT; i++)
        as[i] = i;

    int max = as[0], min = as[0];
    for (i = 0; i < TEST_COUNT; i++)
    {
        max = MAX(max, as[i]);
        min = MIN(min, as[i]);
    }

    EXPECT_EQ(max, TEST_COUNT - 1);
    EXPECT_EQ(min, 0);
}

TEST_CASE(cat)
{
    /* test CAT */
    EXPECT_EQ(CAT(1, 2), 12);
    EXPECT_EQ(CAT(1, 2, 3, 4, 5, 6, 7, 8), 12345678);
    EXPECT_EQ_F(CAT(12, .34), 12.34);
    EXPECT_EQ_F(CAT(12, .34, 567, 890), 12.34567890);
}

TEST_CASE(args)
{

    /* test ARG_COUNT */
    int count = ARG_COUNT(a);
    EXPECT_EQ(count, 1);
    count = ARG_COUNT(1, 2);
    EXPECT_EQ(count, 2);
    count = ARG_COUNT(a, b, c, dd, "e", 12, 43.f);
    EXPECT_EQ(count, 7);
    count = ARG_COUNT(1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       2, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       3, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       4, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       5, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       6, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       7, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       8, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                       9, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    EXPECT_EQ(count, 90);
    
    /* test ARG_LIST */
#define ADD(a) a +
#define STR(a) #a
    int s = ARG_LIST(ADD, 1, 2, 3, 4) 1;
    EXPECT_EQ(s, (1 + 2 + 3 + 4 + 1));
    cstr_t ss = ARG_LIST(STR, 1, 2, 3, 4, 5, 6);
    EXPECT_EQ_S(ss, "123456");
    
    /* test ARG_RECUR */
#define ADD2(a, b) (a + b)
    s = ARG_RECUR(ADD2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);
    EXPECT_EQ(s, (1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 + 11 + 12 + 13));
#define CAT2(a, b) a##b
    s = ARG_RECUR(CAT2, 1, 2, 3, 4, 5, 6);
    EXPECT_EQ(s, 123456);
}

TEST_SUITE(macros)
{
    TEST_RUN(align);
    TEST_RUN(minmax);
    TEST_RUN(cat);
    TEST_RUN(args);
}
