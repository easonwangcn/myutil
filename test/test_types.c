#include "myutil.h"

TEST_CASE(boolean)
{
    EXPECT_LE(sizeof(bool), sizeof(int));
    
    EXPECT_TRUE(true);
    EXPECT_FALSE(false);

    EXPECT_FALSE(!true);
    EXPECT_TRUE(!false);

    EXPECT_FALSE((bool)0);
    EXPECT_TRUE((bool)135);
    EXPECT_TRUE((bool)-20);
}

TEST_CASE(int)
{
    /* Test int */
    EXPECT_EQ(sizeof(int8_t), 1);
    EXPECT_EQ((int8_t)-1, -1);
    EXPECT_EQ((int8_t)0xFF, -1);

    EXPECT_EQ(sizeof(int16_t), 2);
    EXPECT_EQ((int16_t)-1, -1);
    EXPECT_EQ((int16_t)0xFFFF, -1);

    EXPECT_EQ(sizeof(int32_t), 4);
    EXPECT_EQ((int32_t)-1, -1);
    EXPECT_EQ((int32_t)0xFFFFFFFF, -1);

    EXPECT_EQ(sizeof(int64_t), 8);
    EXPECT_EQ((int64_t)-1, -1);
    EXPECT_EQ((int64_t)0xFFFFFFFFFFFFFFFF, -1);
}

TEST_CASE(uint)
{
    /* Test int */
    EXPECT_EQ(sizeof(uint8_t), 1);
    EXPECT_EQ((uint8_t)-1, 0xFF);

    EXPECT_EQ(sizeof(uint16_t), 2);
    EXPECT_EQ((uint16_t)-1, 0xFFFF);

    EXPECT_EQ(sizeof(uint32_t), 4);
    EXPECT_EQ((uint32_t)-1, 0xFFFFFFFF);

    EXPECT_EQ(sizeof(uint64_t), 8);
    EXPECT_EQ((uint64_t)-1, 0xFFFFFFFFFFFFFFFF);
}

TEST_CASE(float)
{
    EXPECT_EQ(sizeof(float32_t), 4);
    EXPECT_EQ(sizeof(float64_t), 8);
}

TEST_CASE(pointer)
{
    EXPECT_EQ(sizeof(ref_t), sizeof(NULL));
    EXPECT_EQ(sizeof(ref_t), sizeof(void *));
    EXPECT_EQ(sizeof(cstr_t), sizeof(NULL));
    EXPECT_EQ(sizeof(cstr_t), sizeof(void *));
    EXPECT_NULL(NULL);
    EXPECT_NULL(null);
}

TEST_SUITE(types)
{
    TEST_RUN_CASE(boolean);
    TEST_RUN_CASE(int);
    TEST_RUN_CASE(uint);
    TEST_RUN_CASE(float);
    TEST_RUN_CASE(pointer);
}
