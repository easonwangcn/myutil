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
 * @file myutil.c
 * @author Eason Wang, talktoeason@gmail.com
 */

#define LOG_LEVEL LOG_INFO
#include "myutil.h"

#include <string.h>

static cstr_t __case_name = NULL;
static size_t __assertion_in_case_count = 0;
static size_t __assertion_failed_in_case_count = 0;

static cstr_t __suite_name = NULL;
static size_t __case_in_suite_count = 0;
static size_t __case_failed_in_suite_count = 0;

static size_t __assertion_count = 0;
static size_t __assertion_failed_count = 0;
static size_t __case_count = 0;
static size_t __case_failed_count = 0;
static size_t __suite_count = 0;
static size_t __suite_failed_count = 0;

/** start a new test cases
 * 
 * the function is usually called by TEST_CASE entry.
 * 
 * @param name: test case name.
 */
void test_case_start(cstr_t name)
{
    __case_name = name;
    __case_in_suite_count++;

    __assertion_in_case_count = 0;
    __assertion_failed_in_case_count = 0;

    if (name != NULL)
    {
        LOGI("Starting test case \"%s - %s\"...", __suite_name, name);
    }
}

/** return current test case name. */
cstr_t test_case_current()
{
    return __case_name;
}

/** print summary when test case done.*/
void test_case_done()
{
    if (__case_name == NULL)
        return;

    __assertion_count += __assertion_in_case_count;
    __assertion_failed_count += __assertion_failed_in_case_count;
    if (__assertion_failed_in_case_count > 0)
        __case_failed_in_suite_count++;

    if (__assertion_failed_in_case_count > 0)
        LOGI("  FAILED (total %ld assertions, %ld failed, %.2f%%).", 
            __assertion_in_case_count, __assertion_failed_in_case_count, 
            __assertion_failed_in_case_count * 100.0 / __assertion_in_case_count);
    else
        LOGI("  PASS (total %ld assertions)",
            __assertion_in_case_count);
}

/** start a new test suite
 * 
 * the function is usually called by TEST_CASE entry.
 * 
 * @param name: test case name.
 */
void test_suite_start(cstr_t name)
{
    __suite_name = name;

    __suite_count++;
    __case_in_suite_count = 0;
    __case_failed_in_suite_count = 0;
    
    if (name != NULL)
    {
        LOGI("");
        LOGI("================================");
        LOGI("Starting test suite \"%s\"...", name);
        LOGI("--------------------------------");
    }
}

/** return current test suite name. */
cstr_t test_suite_current()
{
    return __suite_name;
}

/** print summary when test suite done.*/
void test_suite_done()
{
    if (__suite_name == NULL)
        return;

    __case_count += __case_in_suite_count;
    __case_failed_count += __case_failed_in_suite_count;
    if (__case_failed_in_suite_count > 0)
        __suite_failed_count++;

    LOGI("--------------------------------");
    if (__case_failed_in_suite_count > 0)
    {
        LOGI("FAILED (total %ld test cases %ld failed, %.2f%%)", 
            __case_in_suite_count, __case_failed_in_suite_count, 
            __case_failed_in_suite_count * 100.0 / __case_in_suite_count);
    }
    else
    {
        LOGI("PASS (total %ld test cases)", __case_in_suite_count);
    }
}

#define __MYUTIL_TEST_DONE(level) \
    if (__##level##_failed_count > 0) { \
        LOGI("  total %ld "#level"(s), %ld failed (%.2f%%)", \
            __##level##_count, __##level##_failed_count, __##level##_failed_count * 100.0 / __##level##_count); \
    } else { \
        LOGI("  total %ld "#level"(s) passed", __##level##_count); \
    }

/** print summary when test done.*/
void test_done()
{
    LOGI("");
    LOGI("================================");
    LOGI(__assertion_failed_count > 0 ? "TEST FAILED" : "ALL TEST PASS");
    LOGI("--------------------------------");
    __MYUTIL_TEST_DONE(assertion);
    __MYUTIL_TEST_DONE(case);
    __MYUTIL_TEST_DONE(suite);
    LOGI("");
}

/* Compare 2 string, same as strcmp
 *
 * @param a: the first string.
 * @parem b: the second string.
 * @return same as strcmp
 */
int __myutil_test_compare_string(cstr_t a, cstr_t b)
{
    return strcmp(a, b);
}


/* Condition assertion
 * 
 * @param condition: contition to be test.
 * @return condition input.
 */
bool __myutil_test_expect(bool condition)
{
    __assertion_in_case_count++;

    if (!condition)
    {
        __assertion_failed_in_case_count++;
    }
    return condition;
}

/** Print message header for error assert
 * 
 * @param sa: the first parameter.
 * @param sb: the seconds parameter.
 * @param sop: op to compare two parameters.
 * @param sfile: source file name.
 * @param line: assertion line index in the file.
 */
static void __myutil_test_log_error_assert_head(cstr_t sa, cstr_t sb, cstr_t sop, cstr_t sfile, int line)
{
    LOGE("assertion failed");
    LOGE("    at \"%s\", line %d", sfile, line);
    LOGE("    expect (%s) %s (%s)", sa, sop, sb);
}

/* log error function implement */
#define __MYUTIL_TEST_LOG_ERROR_ASSERT_IMPL(type, transcode) \
    __MYUTIL_TEST_LOG_ERROR_ASSERT(type) \
    { \
        __myutil_test_log_error_assert_head(sa, sb, sop, sfile, line); \
        LOGE("  actual (%"#transcode") vs (%"#transcode")", a, b); \
    }

__MYUTIL_TEST_LOG_ERROR_ASSERT_IMPL(int64_t, lld);
__MYUTIL_TEST_LOG_ERROR_ASSERT_IMPL(uint64_t, llu);
__MYUTIL_TEST_LOG_ERROR_ASSERT_IMPL(double, lf);
__MYUTIL_TEST_LOG_ERROR_ASSERT_IMPL(ptr_t, p);
__MYUTIL_TEST_LOG_ERROR_ASSERT_IMPL(cstr_t, s);

