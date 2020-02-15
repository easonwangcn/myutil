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
 * @file double_list.h
 * @author Eason Wang, talktoeason@gmail.com
 */

#ifndef __MYUTIL_DOUBLE_LIST_H__
#define __MYUTIL_DOUBLE_LIST_H__

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma anon_unions

/* ---------------------------------------------------------------------------
 *  DbList interface
 * ------------------------------------------------------------------------ */

/**
 * Class DbList.
 * 
 * A double chain list node.
 */
typedef struct _DbList
{
    struct _DbList *next;   /**< next node pointer */
    struct _DbList *prev;       /**< prev node pointer */
} DbList;

/**
 * Init list iterator by list head.
 * 
 * @param self: the ListIter object to be init.
 * @param head: the head of list.
 */
static inline void DbList_init(DbList *self)
{
    self->next = self;
    self->prev = self;
};

/* ---------------------------------------------------------------------------
 *  DbListIter interface
 * ------------------------------------------------------------------------ */

/**
 * Class ListIter.
 * 
 * A list iterator.
 */
typedef struct _DbListIter
{
    DbList *current;
    DbList *head;
} DbListIter;

/**
 * Init list iterator by double list head.
 * 
 * @param self: the ListIter object to be init.
 * @param head: the head of double list.
 */
static inline void DbListIter_init(DbListIter *self, DbList *head)
{
    self->current = head;
    self->head = NULL;
};

/**
 * New double list iterator by list head.
 * 
 * @param head: the head of list.
 * 
 * @return a ListIter object start with head.
 */
static inline DbListIter DbListIter_new(DbList *head)
{
    DbListIter iter;
    DbListIter_init(&iter, head);
    return iter;
};

/**
 * check if iterator has previouse node.
 * 
 * @param self: the ListIter object pointer.
 * @return a booean, false for iterator reaches the head, otherwise true.
 */
static inline bool DbListIter_hasPrev(DbListIter *self)
{
    return self->current != NULL && self->current != self->head;
};

/**
 * check if iterator has next node.
 * 
 * @param self: the ListIter object pointer.
 * @return a booean, false for iterator reaches the end, otherwise true.
 */
static inline bool DbListIter_hasNext(DbListIter *self)
{
    return self->current != NULL && self->current->next != self->head;
};

/**
 * Get current double list node.
 * 
 * @param self: the ListIter object pointer.
 * 
 * @return a pointer to current double list.
 */
static inline DbList *DbListIter_current(DbListIter *self)
{
    return self->current;
};

/**
 * Get double list's head node.
 * 
 * @param self: the ListIter object pointer.
 * 
 * @return a pointer to double list's head node.
 */
static inline DbList *DbListIter_head(DbListIter *self)
{
    return self->head == NULL? self->current: self->head;
};

/**
 * Move iterator to next node.
 * 
 * @param self: the ListIter object pointer.
 * @return a booean, false for iterator reaches the end, otherwise true.
 */
bool DbListIter_next(DbListIter *self);

/**
 * Move iterator to previouse node.
 * 
 * @param self: the ListIter object pointer.
 * @return a booean, false for iterator reaches the head, otherwise true.
 */
bool DbListIter_prev(DbListIter *self);

/**
 * Remove current item from double list.
 * 
 * @param self: the ListIter object pointer.
 * @param head: the head pointer which be may updated after removal. 
 *      Or NULL if don't care.
 * 
 * @return a pointer to removed node.
 */
DbList *DbListIter_remove(DbListIter *self, DbList **head);

/**
 * Insert new node to current position of double list.
 * 
 * @param self: the ListIter object pointer.
 * @param node: the node to be insert.
 * @param head: the head pointer which be may updated after removal. 
 *      Or NULL if don't care.
 * 
 * @return a pointer to removed node, or NULL if failed.
 */
DbList *DbListIter_insert(DbListIter *self, DbList *node, DbList **head);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __MYUTIL_DOUBLE_LIST_H__ */
