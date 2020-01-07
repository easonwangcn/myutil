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
 * @file allocator.c
 * @author Eason Wang, talktoeason@gmail.com
 */

#include "myutil.h"

static void *__myutil_allocator_StaticAllocator_alloc(Allocator *self, size_t size);
static void *__myutil_allocator_StaticAllocator_free(Allocator *self, void *p);
static size_t __myutil_allocator_StaticAllocator_capacity(Allocator *self);
static size_t __myutil_allocator_StaticAllocator_available(Allocator *self);

static Allocator_vt const __staticAllocator_vt = {
    .alloc = __myutil_allocator_StaticAllocator_alloc,
    .free = NULL,                                               /* static allocator cannot free */
    .capacity = __myutil_allocator_StaticAllocator_capacity,
    .available = __myutil_allocator_StaticAllocator_available,
};

typedef struct _StaticAllocatorClass
{
    Allocator super;
    
    size_t capacity;
    size_t used;
} StaticAllocatorClass;

typedef struct _StaticAllocatorBlock
{

    size_t size;
} StaticAllocatorBlock;


/** 
 * Create a static allocator from existing buffer.
 * 
 * An static allocator can only allocate, not free.
 * 
 * @param size: the buffer size.
 * @param buf: the memory buffer pointer.
 * 
 * @return the handler to allocator.
 */
Allocator *StaticAllocator(size_t size, void *buf)
{
   /* Too small buffer. */
    if (size <= sizeof(StaticAllocator))
        return NULL;

    /* Initial object in the beginning of the buffer. */
    StaticAllocatorClass *_self = (StaticAllocatorClass *)buf;
    _self->super.vt = &__staticAllocator_vt;
    
    _self->capacity = size;
    _self->used = sizeof(StaticAllocatorClass);
    
    // printf("new %d @ %p(%d, %d)\n", size, _self, _self->capacity, _self->used);
    /* return super pointer */
    return &_self->super;
}

static void *__myutil_allocator_StaticAllocator_alloc(Allocator *self, size_t size)
{
    return NULL;
}

static void *__myutil_allocator_StaticAllocator_free(Allocator *self, void *p)
{
    return p;
}

static size_t __myutil_allocator_StaticAllocator_capacity(Allocator *self)
{
    return 0;
}

static size_t __myutil_allocator_StaticAllocator_available(Allocator *self)
{
    return 0;
}

