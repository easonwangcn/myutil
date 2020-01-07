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
 * @file macros.h
 * @author Eason Wang, talktoeason@gmail.com
 */
 
#ifndef __MYUTIL_MACROS_H__
#define __MYUTIL_MACROS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* ----------------------------------------------------------------
 * Number tools
 * ------------------------------------------------------------- */

/** align an integer
 * 
 * e.g. 
 * ```
 * ALIGN(0x54321, 4) = 0x54330
 * ALIGN(0x54321, 8) = 0x54400
 * ```
 * 
 * @param a: the integer to be aligned.
 * @param align: the count of aligned bits, should be power of 2.
 */
#define ALIGN(a, align) (((a) + (align) - 1) & ~((align) - 1))

/** Get the maximun one of arguments. */
#define MAX(...) ARG_RECUR(__MYUTIL_MACROS_MAX2, __VA_ARGS__)
/** Get the minimal one of arguments. */
#define MIN(...) ARG_RECUR(__MYUTIL_MACROS_MIN2, __VA_ARGS__)
/** @cond DO_NOT_DOCUMENT */
#define __MYUTIL_MACROS_MAX2(a, b) __MYUTIL_MACROS_MAX2_(a, b)
#define __MYUTIL_MACROS_MAX2_(a, b)  ((a) > (b) ? (a) : (b))
#define __MYUTIL_MACROS_MIN2(a, b) __MYUTIL_MACROS_MIN2_(a, b)
#define __MYUTIL_MACROS_MIN2_(a, b)  ((a) < (b) ? (a) : (b))
/** @endcond */

/* ----------------------------------------------------------------
 * Cat
 * ------------------------------------------------------------- */

/** cat several augument together
 * 
 * e.g. `CAT(a, b, c) = abc`
 */
#define CAT(...) ARG_RECUR(__MYUTIL_MACROS_CAT2, __VA_ARGS__)
/** @cond DO_NOT_DOCUMENT */
#define __MYUTIL_MACROS_CAT2(a, b) __MYUTIL_MACROS_CAT2_(a, b)
#define __MYUTIL_MACROS_CAT2_(a, b) a##b
/** @endcond */

/* ----------------------------------------------------------------
 * Arguments
 * ------------------------------------------------------------- */

/** count arguments, up to max 99 args. */
#define ARG_COUNT(...) __MYUTIL_MACROS_ARG_COUNT(_, ##__VA_ARGS__, __MYUTIL_MACROS_ARG_COUNT_HELPER)

/** @cond DO_NOT_DOCUMENT */
#define __MYUTIL_MACROS_ARG_COUNT(...) __MYUTIL_MACROS_ARG_COUNT_(__VA_ARGS__)
#define __MYUTIL_MACROS_ARG_COUNT_(\
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _10, \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
    _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
    _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
    _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, \
    _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, \
    _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, \
    _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, \
    N, ...) N
#define __MYUTIL_MACROS_ARG_COUNT_HELPER \
    99, 98, 97, 96, 95, 94, 93, 92, 91, 90, \
    89, 88, 87, 86, 85, 84, 83, 82, 81, 80, \
    79, 78, 77, 76, 75, 74, 73, 72, 71, 70, \
    69, 68, 67, 66, 65, 64, 63, 62, 61, 60, \
    59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
    49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
    39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
    29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
    19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
    9, 8, 7, 6, 5, 4, 3, 2, 1, 0
/** @endcond */

/** call function along all the arguments. up to max 99 args.
 * 
 * E.g. `ARG_LIST(func, 1, 2, 3, 4)` will be expanded as `func(1) func(2) func(3) func(4)`
 * 
 * Usually `func` is another macro.
 */
#define ARG_LIST(func, ...) ARG_LIST1(__MYUTIL_MACROS_ARG_LIST_FUNC, func, __VA_ARGS__)

/** @cond DO_NOT_DOCUMENT */
#define __MYUTIL_MACROS_ARG_LIST_FUNC(func, arg) func(arg)
/** @endcond */

/** call function along all the arguments. up to max 99 args.
 * 
 * Other than ARG_LIST, ARG_LIST1 has an special arguments that is always fill to functions.
 * 
 * E.g. ARG_LIST(func, 0, 1, 2, 3, 4) will be expanded as func(0, 1) func(0, 2) func(0, 3) func(0, 4)
 * Usually func is another macro.
 */
#define ARG_LIST1(func, arg0, ...) __MYUTIL_MACROS_ARG_LIST1_(func, arg0, __VA_ARGS__)

/** @cond DO_NOT_DOCUMENT */
#define __MYUTIL_MACROS_ARG_LIST1_(func, arg0, ...) __MYUTIL_MACROS_CAT2(__MYUTIL_MACROS_ARG_LIST, ARG_COUNT(__VA_ARGS__))(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST0(func)
#define __MYUTIL_MACROS_ARG_LIST1(func, arg0, arg) func(arg0, arg)
#define __MYUTIL_MACROS_ARG_LIST2(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST1(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST3(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST2(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST4(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST3(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST5(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST4(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST6(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST5(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST7(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST6(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST8(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST7(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST9(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST8(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST10(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST9(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST11(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST10(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST12(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST11(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST13(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST12(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST14(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST13(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST15(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST14(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST16(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST15(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST17(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST16(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST18(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST17(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST19(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST18(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST20(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST19(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST21(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST20(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST22(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST21(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST23(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST22(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST24(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST23(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST25(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST24(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST26(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST25(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST27(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST26(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST28(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST27(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST29(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST28(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST30(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST29(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST31(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST30(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST32(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST31(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST33(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST32(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST34(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST33(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST35(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST34(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST36(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST35(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST37(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST36(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST38(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST37(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST39(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST38(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST40(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST39(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST41(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST40(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST42(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST41(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST43(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST42(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST44(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST43(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST45(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST44(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST46(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST45(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST47(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST46(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST48(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST47(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST49(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST48(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST50(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST49(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST51(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST50(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST52(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST51(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST53(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST52(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST54(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST53(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST55(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST54(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST56(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST55(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST57(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST56(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST58(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST57(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST59(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST58(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST60(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST59(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST61(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST60(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST62(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST61(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST63(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST62(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST64(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST63(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST65(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST64(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST66(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST65(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST67(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST66(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST68(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST67(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST69(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST68(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST70(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST69(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST71(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST70(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST72(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST71(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST73(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST72(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST74(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST73(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST75(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST74(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST76(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST75(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST77(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST76(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST78(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST77(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST79(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST78(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST80(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST79(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST81(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST80(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST82(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST81(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST83(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST82(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST84(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST83(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST85(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST84(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST86(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST85(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST87(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST86(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST88(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST87(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST89(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST88(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST90(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST89(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST91(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST90(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST92(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST91(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST93(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST92(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST94(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST93(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST95(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST94(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST96(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST95(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST97(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST96(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST98(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST97(func, arg0, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_LIST99(func, arg0, arg, ...) func(arg0, arg) __MYUTIL_MACROS_ARG_LIST98(func, arg0, __VA_ARGS__)
/** @endcond */

/** ARG_RECUR, call function with all the arguments. up to max 99 args. 
 * 
 * E.g. `ARG_RECUR(func, 1, 2, 3, 4)` will be expanded as `func(1, func(2, func(3, func(4))))`
 * 
 * Usually `func` is another macro.
 */
#define ARG_RECUR(func, ...) __MYUTIL_MACROS_ARG_RECUR_(func, __VA_ARGS__)

/** @cond DO_NOT_DOCUMENT */
#define __MYUTIL_MACROS_ARG_RECUR_(func, ...) __MYUTIL_MACROS_CAT2(__MYUTIL_MACROS_ARG_RECUR, ARG_COUNT(__VA_ARGS__))(func, __VA_ARGS__)
#define __MYUTIL_MACROS_ARG_RECUR0(func)
#define __MYUTIL_MACROS_ARG_RECUR1(func, arg)
#define __MYUTIL_MACROS_ARG_RECUR2(func, arg1, arg2) func(arg1, arg2)
#define __MYUTIL_MACROS_ARG_RECUR3(func, arg, ...) __MYUTIL_MACROS_ARG_RECUR2(func, arg, __MYUTIL_MACROS_ARG_RECUR2(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR4(func, arg, ...) __MYUTIL_MACROS_ARG_RECUR2(func, arg, __MYUTIL_MACROS_ARG_RECUR3(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR5(func, arg, ...) __MYUTIL_MACROS_ARG_RECUR2(func, arg, __MYUTIL_MACROS_ARG_RECUR4(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR6(func, arg, ...) __MYUTIL_MACROS_ARG_RECUR2(func, arg, __MYUTIL_MACROS_ARG_RECUR5(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR7(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR6(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR8(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR7(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR9(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR8(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR10(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR9(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR11(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR10(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR12(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR11(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR13(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR12(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR14(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR13(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR15(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR14(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR16(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR15(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR17(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR16(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR18(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR17(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR19(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR18(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR20(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR19(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR21(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR20(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR22(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR21(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR23(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR22(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR24(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR23(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR25(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR24(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR26(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR25(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR27(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR26(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR28(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR27(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR29(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR28(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR30(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR29(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR31(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR30(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR32(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR31(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR33(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR32(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR34(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR33(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR35(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR34(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR36(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR35(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR37(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR36(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR38(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR37(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR39(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR38(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR40(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR39(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR41(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR40(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR42(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR41(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR43(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR42(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR44(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR43(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR45(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR44(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR46(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR45(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR47(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR46(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR48(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR47(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR49(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR48(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR50(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR49(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR51(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR50(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR52(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR51(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR53(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR52(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR54(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR53(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR55(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR54(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR56(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR55(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR57(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR56(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR58(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR57(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR59(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR58(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR60(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR59(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR61(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR60(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR62(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR61(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR63(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR62(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR64(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR63(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR65(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR64(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR66(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR65(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR67(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR66(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR68(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR67(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR69(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR68(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR70(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR69(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR71(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR70(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR72(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR71(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR73(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR72(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR74(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR73(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR75(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR74(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR76(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR75(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR77(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR76(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR78(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR77(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR79(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR78(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR80(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR79(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR81(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR80(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR82(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR81(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR83(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR82(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR84(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR83(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR85(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR84(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR86(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR85(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR87(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR86(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR88(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR87(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR89(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR88(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR90(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR89(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR91(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR90(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR92(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR91(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR93(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR92(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR94(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR93(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR95(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR94(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR96(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR95(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR97(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR96(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR98(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR97(func, __VA_ARGS__))
#define __MYUTIL_MACROS_ARG_RECUR99(func, arg, ...) func(arg, __MYUTIL_MACROS_ARG_RECUR98(func, __VA_ARGS__))
/** @endcond */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __MYUTIL_MACROS_H__ */
