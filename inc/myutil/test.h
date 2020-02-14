/* Copyright (C) 2020 Eason Wang, talktoeason@gmail.com
 * This file is part of the MyUtil Library.
 * 
 * MyUtil library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU GENERAL PUBLIC LICENSE as published by the Free
 * Software Foundation; either version 3.0 of the License, or (at your option)
 * any later version.
 * 
 * The MyUtil Library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU GENERAL PUBLIC LICENSE
 * for more details.
 * 
 * You should have received a copy of the GNU GENERAL PUBLIC LICENSE along
 * with the MyUtil Library; if not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file test.h
 * @author Eason Wang, talktoeason@gmail.com
 */

#ifndef __MYUTIL_TEST_H__
#define __MYUTIL_TEST_H__

#include "types.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------
 *  Test macros
 * ------------------------------------------------------------------------ */

/** test main entry
 * 
 * The main entry implements main function and run all test suite.
 * 
 * Usage
 * -----
 * ```cpp
 * TEST_MAIN(suite0, suite1, ...);
 * ```
 */
#define TEST_MAIN(...)  TEST_IMPORT(__VA_ARGS__); __MYUTIL_TEST_MAIN(__VA_ARGS__)

#define TEST_IMPORT(...)  __MYUTIL_TEST_DECL(__VA_ARGS__); __MYUTIL_TEST_RUN_DECL(__VA_ARGS__);
#define TEST_RUN() __myutil_test_run()

/** test case entry */
#define TEST_CASE(test_case) static void __MYUTIL_TEST_CASE_ENTRY_IMPL_NAME(test_case)(void); \
    static void __MYUTIL_TEST_CASE_ENTRY_NAME(test_case)(void) { \
        test_case_start(#test_case); \
        __MYUTIL_TEST_CASE_ENTRY_IMPL_NAME(test_case)(); \
        test_case_done(); \
    } \
    static void __MYUTIL_TEST_CASE_ENTRY_IMPL_NAME(test_case)(void)

/** test suite entry */
#define TEST_SUITE(suite, ...) static void __MYUTIL_TEST_SUITE_ENTRY_IMPL_NAME(suite)(void); \
    void __MYUTIL_TEST_SUITE_ENTRY_NAME(suite)(void) { \
        test_suite_start(#suite); \
        __MYUTIL_TEST_SUITE_ENTRY_IMPL_NAME(suite)(); \
        test_suite_done(); \
    } \
    static void __MYUTIL_TEST_SUITE_ENTRY_IMPL_NAME(suite)(void)

/** run test cases */
#define TEST_RUN_CASE(...) ARG_LIST(__MYUTIL_TEST_RUN_CASE, __VA_ARGS__)

/** start a new test cases
 * 
 * the function is usually called by TEST_CASE entry.
 * 
 * @param name: test case name.
 */
void test_case_start(cstr_t name);

/** return current test case name. */
cstr_t test_case_current(void);

/** print summary when test case done.
 * 
 * @return failed assertion count.
 */
int test_case_done(void);

/** start a new test suite
 * 
 * the function is usually called by TEST_CASE entry.
 * 
 * @param name: test case name.
 */
void test_suite_start(cstr_t name);

/** return current test suite name.
 * 
 * @return failed test case count.
 */
cstr_t test_suite_current(void);

/** print summary when test suite done.*/
int test_suite_done(void);

/** print summary when test done.
 * 
 * @return failed test suite count.
 */
int test_done(void);

/** @cond DO_NOT_DOCUMENT */
#define __MYUTIL_TEST_CASE_ENTRY_NAME(test_case) __myutil_test_##test_case##_entry
#define __MYUTIL_TEST_CASE_ENTRY_IMPL_NAME(test_case) __myutil_test_##test_case##_entry_impl
#define __MYUTIL_TEST_SUITE_ENTRY_NAME(suite) __myutil_test_##suite##_entry
#define __MYUTIL_TEST_SUITE_ENTRY_IMPL_NAME(suite) __myutil_test_##suite##_entry_impl
#define __MYUTIL_TEST_RUN_CASE(test_case) __MYUTIL_TEST_CASE_ENTRY_NAME(test_case)();

#define __MYUTIL_TEST_DECL(...) ARG_LIST(__MYUTIL_TEST_DECL_, __VA_ARGS__)
#define __MYUTIL_TEST_DECL_(suite) void __MYUTIL_TEST_SUITE_ENTRY_NAME(suite)(void);
#define __MYUTIL_TEST_RUN_DECL(...) int __myutil_test_run() { \
        __MYUTIL_TEST_MAIN_RUN_SUITE(__VA_ARGS__)\
        return test_done(); \
    }

#define __MYUTIL_TEST_MAIN(...) \
    void __myutil_test_pre_main(void); \
    int main(void) { \
        __myutil_test_pre_main(); \
        return __myutil_test_run(); \
    } \
    void __myutil_test_pre_main(void)

#define __MYUTIL_TEST_MAIN_RUN_SUITE(...) ARG_LIST(__MYUTIL_TEST_MAIN_RUN_SUITE_, __VA_ARGS__)

#define __MYUTIL_TEST_MAIN_RUN_SUITE_(suite) __MYUTIL_TEST_SUITE_ENTRY_NAME(suite)();
/** @endcond */

/* ---------------------------------------------------------------------------
 *  Assertion macros
 * ------------------------------------------------------------------------ */

/* assertions */
#define EXPECT_EQ(a, b) __MYUTIL_TEST_EXPECT(a, b, ==, uint64_t)    /**< test if 2 integers is equals */
#define EXPECT_NE(a, b) __MYUTIL_TEST_EXPECT(a, b, !=, uint64_t)    /**< test if 2 integers is not equals */
#define EXPECT_LE(a, b) __MYUTIL_TEST_EXPECT(a, b, <=, uint64_t)    /**< test if integer a is less or equals to integer b */
#define EXPECT_LT(a, b) __MYUTIL_TEST_EXPECT(a, b, <, uint64_t)     /**< test if integer a is less than integer b */
#define EXPECT_GE(a, b) __MYUTIL_TEST_EXPECT(a, b, >=, uint64_t)    /**< test if integer a is greater or equals to integer b */
#define EXPECT_GT(a, b) __MYUTIL_TEST_EXPECT(a, b, >, uint64_t)     /**< test if integer a is greater than integer b */

#define EXPECT_EQ_F(a, b) __MYUTIL_TEST_EXPECT(a, b, ==, double)    /**< test if 2 floats is equals */
#define EXPECT_NE_F(a, b) __MYUTIL_TEST_EXPECT(a, b, !=, double)    /**< test if 2 floats is not equals */
#define EXPECT_LE_F(a, b) __MYUTIL_TEST_EXPECT(a, b, <=, double)    /**< test if float a is less or equals to float b */
#define EXPECT_LT_F(a, b) __MYUTIL_TEST_EXPECT(a, b, <, double)     /**< test if float a is less than float b */
#define EXPECT_GE_F(a, b) __MYUTIL_TEST_EXPECT(a, b, >=, double)    /**< test if float a is greater or equals to float b */
#define EXPECT_GT_F(a, b) __MYUTIL_TEST_EXPECT(a, b, >, double)     /**< test if float a is greater than float b */

#define EXPECT_EQ_S(a, b) __MYUTIL_TEST_EXPECT_S(a, b, ==)          /**< test if 2 string is equals, see strcmp */
#define EXPECT_NE_S(a, b) __MYUTIL_TEST_EXPECT_S(a, b, !=)          /**< test if 2 string is not equals, see strcmp */
#define EXPECT_LE_S(a, b) __MYUTIL_TEST_EXPECT_S(a, b, <=)          /**< test if string a is less or equals to string b, see strcmp */
#define EXPECT_LT_S(a, b) __MYUTIL_TEST_EXPECT_S(a, b, <)           /**< test if string a is less than string b, see strcmp */
#define EXPECT_GE_S(a, b) __MYUTIL_TEST_EXPECT_S(a, b, >=)          /**< test if string a is greater or equals to string b, see strcmp */
#define EXPECT_GT_S(a, b) __MYUTIL_TEST_EXPECT_S(a, b, >)           /**< test if string a is greater than string b, see strcmp */

#define EXPECT_TRUE(a) EXPECT_EQ(a, true)       /**< test if boolean a is true */
#define EXPECT_FALSE(a) EXPECT_EQ(a, false)     /**< test if boolean a is flase */
#define EXPECT_ZERO(a) EXPECT_EQ(a, 0)          /**< test if integer a is 0 */
#define EXPECT_NOT_ZERO(a) EXPECT_NE(a, 0)      /**< test if integer a is not 0 */
#define EXPECT_NULL(a) EXPECT_EQ(a, NULL)       /**< test if pointer a is NULL */
#define EXPECT_NOT_NULL(a) EXPECT_NE(a, NULL)   /**< test if pointer a is not NULL */

/** @cond DO_NOT_DOCUMENT */

/* ---------------------------------------------------------------------------
 *  Assertion helper
 * ------------------------------------------------------------------------ */

/* Expect implementation */
#define __MYUTIL_TEST_EXPECT(a, b, op, type) __MYUTIL_TEST_EXPECT_(((type)(a) op (type)(b)), a, b, op, type)
#define __MYUTIL_TEST_EXPECT_S(a, b, op) __MYUTIL_TEST_EXPECT_((__myutil_test_compare_string((a), (b)) op 0), a, b, op, cstr_t)

#define __MYUTIL_TEST_EXPECT_(condition, a, b, op, type) do { \
        if (!__myutil_test_expect(condition)) \
            __MYUTIL_TEST_LOG_ERROR_ASSERT_NAME(type)((type)(a), (type)(b), #a, #b, #op, __FILE__, __LINE__); \
    } while (0)

/* Log expect error */
#define __MYUTIL_TEST_LOG_ERROR_ASSERT_NAME(type) __myutil_test_log_error_##type
#define __MYUTIL_TEST_LOG_ERROR_ASSERT(type) void __MYUTIL_TEST_LOG_ERROR_ASSERT_NAME(type)( \
        type a, type b, cstr_t sa, cstr_t sb, cstr_t sop, cstr_t sfile, int line)

/* Log error function declare for different type. */
__MYUTIL_TEST_LOG_ERROR_ASSERT(int64_t);
__MYUTIL_TEST_LOG_ERROR_ASSERT(uint64_t);
__MYUTIL_TEST_LOG_ERROR_ASSERT(double);
__MYUTIL_TEST_LOG_ERROR_ASSERT(cstr_t);

/* Compare 2 string, same as strcmp
 *
 * @param a: the first string.
 * @parem b: the second string.
 * @return same as strcmp
 */
int __myutil_test_compare_string(cstr_t a, cstr_t b);

/* Condition assertion
 * 
 * @param condition: contition to be test.
 * @return condition input.
 */
bool __myutil_test_expect(bool condition);
/** @endcond */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __MYUTIL_TEST_H__ */
