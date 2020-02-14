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
 * @file allocator.h
 * @author Eason Wang, talktoeason@gmail.com
 */

#ifndef __MYUTIL_ALLOCATOR_H__
#define __MYUTIL_ALLOCATOR_H__

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------
 *  Allocator interface
 * ------------------------------------------------------------------------ */

struct _Allocator;

/**
 * Class Allocator virtual table
 */
typedef struct _Allocator_vt
{
    void *(*alloc)(struct _Allocator *self, size_t size); /**< Allocate memory from allocator. */
    void (*free)(struct _Allocator *self, void *p);       /**< Free allocated memory to allocator. */
    size_t (*capacity)(struct _Allocator *self);          /**< Return the whole capacity of allocator. */
    size_t (*available)(struct _Allocator *self);         /**< Return the available memories of allocator. */
} Allocator_vt;

/**
 * Class Allocator.
 * 
 * It is a pure interface only to provide an virtual table.
 */
typedef struct _Allocator
{
    Allocator_vt const *vt;  /**< virtual table. */

} Allocator;

/**
 * Allocate memory from allocator.
 * 
 * @param self: the allocator.
 * @param size: the size of memory to be allocate.
 * 
 * @return the allocated memory pointer, or NULL if failed.
 */
static inline void *Allocator_alloc(Allocator *self, size_t size)
{
    return self->vt->alloc(self, size);
};

/** Fast function to allocate a class.
 * 
 * @param self: the allocator.
 * @param cls: class name.
 */
#define Allocator_new(self, cls) ((cls *)Allocator_alloc(self, sizeof(cls)))

/**
 * Free memory to allocator.
 * 
 * @param self: the allocator.
 * @param p: the memory pointer to be free.
 */
static inline void Allocator_free(Allocator *self, void *p)
{
    self->vt->free(self, p);
};

/** 
 * Get the whole capacity of allocator.
 * 
 * @param self: the allocator.
 * @return the capacity of allocator.
 */
static inline size_t Allocator_capacity(Allocator *self)
{
    return self->vt->capacity(self);
};

/** 
 * Get the free memory size of allocator.
 * 
 * @param self: the allocator.
 * @return the remain memory size of allocator.
 */
static inline size_t Allocator_available(Allocator *self)
{
    return self->vt->available(self);
};

/* ---------------------------------------------------------------------------
 * Static allocator
 * ------------------------------------------------------------------------ */

/** 
 * Create a static allocator from existing buffer.
 * 
 * An static allocator can only allocate, not free.
 * 
 * @param size is the buffer size.
 * @param buf is the memory buffer pointer.
 * 
 * @return the handler to allocator.
 */
Allocator *StaticAllocator(size_t size, void *buf);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __MYUTIL_ALLOCATOR_H__ */
