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
 * @file types.h
 * @author Eason Wang, talktoeason@gmail.com
 */
 
#ifndef __MYUTIL_TYPES_H__
#define __MYUTIL_TYPES_H__

#include <stdint.h>     /* uint32_t, int32_t, uint16_t, int16_t, uint8_t, int8_t */
#include <stdbool.h>    /* bool, true, false */
#include <stddef.h>     /* NULL, size_t */

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------
 *  Types
 * ------------------------------------------------------------------------ */

typedef uint8_t byte;       /**< byte type, 8 bits, unsigned. */

typedef float float32_t;    /**< 32 bits float type */
typedef double float64_t;   /**< 64 bits float type */

typedef char const *cstr_t; /**< const string pointer */

typedef void *ptr_t;        /**< pointer */
#define null NULL           /**< null pointer constant */

/* ---------------------------------------------------------------------------
 *  Class
 * ------------------------------------------------------------------------ */

/** down cast object pointer from super */
#define DOWN_CAST(ptr, type) DOWN_CAST_FROM(ptr, type, super)

/** down cast object pointer from super type */
#define DOWN_CAST_FROM(ptr, type, field) ((type *)((uint8_t *)ptr - (size_t)&(((type *)0)->field)))

/** up cast object pointer to super */
#define UP_CAST(obj, type) ((type *)(&obj->super))

/** up cast object to super */
#define UP_CAST_OBJ(ptr, type) ((type *)(&ptr.super))

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __MYUTIL_TYPES_H__ */
