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

#ifndef __MYUTIL_LIST_H__
#define __MYUTIL_LIST_H__

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma anon_unions

/* ---------------------------------------------------------------------------
 *  List interface
 * ------------------------------------------------------------------------ */

/**
 * Class List.
 * 
 * A chain list node.
 */
typedef struct _List
{
    struct _List *next;   /**< next node pointer */
} List;

/* ---------------------------------------------------------------------------
 *  DoubleList interface
 * ------------------------------------------------------------------------ */

/**
 * Class DoubleList.
 * 
 * A double chain list node.
 */
typedef struct _DoubleList
{
    union {
        List super;                 /**< super list class */
        struct _DoubleList *next;   /**< next node pointer */
    };
    struct _DoubleList *prev;       /**< prev node pointer */
} DoubleList;

/* ---------------------------------------------------------------------------
 *  ListIter interface
 * ------------------------------------------------------------------------ */

/**
 * Class ListIter.
 * 
 * A list iterator.
 */
typedef struct _ListIter
{
    List *node0;
    List *node1;
} ListIter;

/**
 * Init list iterator by list head.
 * 
 * @param self: the ListIter object to be init.
 * @param head: the head of list.
 */
void ListIter_init(ListIter *self, List *head);

/**
 * New list iterator by list head.
 * 
 * @param head: the head of list.
 * 
 * @return a ListIter object start with head.
 */
static inline ListIter ListIter_new(List *head)
{
    ListIter iter;
    ListIter_init(&iter, head);
    return iter;
}

/**
 * check if iterator has next node.
 * 
 * @param self: the ListIter object pointer.
 * @return a booean, false for iterator reaches the end, otherwise true.
 */
bool ListIter_hasNext(ListIter *self);

/**
 * Move iterator to next node.
 * 
 * @param self: the ListIter object pointer.
 * @return a booean, false for iterator reaches the end, otherwise true.
 */
bool ListIter_next(ListIter *self);

/**
 * Get current list node.
 * 
 * @param self: the ListIter object pointer.
 * 
 * @return a pointer to current list.
 */
List *ListIter_current(ListIter *self);

/**
 * Remove current item from list.
 * 
 * @param self: the ListIter object pointer.
 * @param head: the head pointer which be may updated after removal. 
 *      Or NULL if don't care.
 * 
 * @return a pointer to removed node.
 */
List *ListIter_remove(ListIter *self, List **head);

/**
 * Insert new node to current position.
 * 
 * @param self: the ListIter object pointer.
 * @param node: the node to be insert.
 * @param head: the head pointer which be may updated after removal. 
 *      Or NULL if don't care.
 * 
 * @return a pointer to removed node, or NULL if failed.
 */
List *ListIter_insert(ListIter *self, List *node, List **head);

/* ---------------------------------------------------------------------------
 *  DoubleListIter interface
 * ------------------------------------------------------------------------ */

/**
 * Init list iterator by double list head.
 * 
 * @param self: the ListIter object to be init.
 * @param head: the head of double list.
 */
void DoubleListIter_init(ListIter *self, DoubleList *head);

/**
 * New double list iterator by list head.
 * 
 * @param head: the head of list.
 * 
 * @return a ListIter object start with head.
 */
static inline ListIter DoubleListIter_new(DoubleList *head)
{
    ListIter iter;
    DoubleListIter_init(&iter, head);
    return iter;
}

/**
 * Move iterator to next node.
 * 
 * @param self: the ListIter object pointer.
 */
void DoubleListIter_next(ListIter *self);

/**
 * Get current double list node.
 * 
 * @param self: the ListIter object pointer.
 * 
 * @return a pointer to current double list.
 */
List *DoubleListIter_current(ListIter *self);

/**
 * Remove current item from double list.
 * 
 * @param self: the ListIter object pointer.
 * @param head: the head pointer which be may updated after removal. 
 *      Or NULL if don't care.
 * 
 * @return a pointer to removed node.
 */
DoubleList *DoubleListIter_remove(ListIter *self, DoubleList **head);

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
List *DoubleListIter_insert(ListIter *self, DoubleList *node, DoubleList **head);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __MYUTIL_ALLOCATOR_H__ */
