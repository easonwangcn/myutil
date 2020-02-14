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
 * @file list.c
 * @author Eason Wang, talktoeason@gmail.com
 */

#include "myutil.h"

/* ---------------------------------------------------------------------------
 *  ListIter implements
 * ------------------------------------------------------------------------ */

/**
 * Init list iterator by list head.
 * 
 * @param self: the ListIter object to be init.
 * @param head: the head of list.
 */
void ListIter_init(ListIter *self, List *head)
{
    self->node0 = self->node1 = head;
}

/**
 * check if iterator has next node.
 * 
 * @param self: the ListIter object pointer.
 * @return a booean, false for iterator reaches the end, otherwise true.
 */
bool ListIter_hasNext(ListIter *self)
{
    return self->node0 != NULL && self->node0->next != NULL;
}

/**
 * Move iterator to next node.
 * 
 * @param self: the ListIter object pointer.
 */
bool ListIter_next(ListIter *self)
{
    if (self->node0 == NULL)
    {
        /* at the end */
        return false;
    }
    
    if (self->node0 == self->node1)
    {
        /* initial status, move to first one */
        self->node1 = NULL;
    }
    else
    {
        /* move to next node */
        self->node1 = self->node0;
        self->node0 = self->node0->next;
    }
    
    return self->node0 != NULL;
}

/**
 * Get current list node.
 * 
 * @param self: the ListIter object pointer.
 * 
 * @return a pointer to current list.
 */
List *ListIter_current(ListIter *self)
{
    if (self->node0 == self->node1)
    {
        /* initial status, not started */
        return NULL;
    }

    return self->node0;
}

/**
 * Remove current item from list. 
 * 
 * Iterator will be reset, call next() before next action.
 * 
 * @param self: the ListIter object pointer.
 * @param head: the head pointer which be may updated after removal. 
 *      Or NULL if don't care.
 * 
 * @return a pointer to removed node.
 */
List *ListIter_remove(ListIter *self, List **head)
{
    if (self->node0 == self->node1 || self->node0 == NULL)
    {
        /* initial status or end */
        return NULL;
    }

    List *node = self->node0;
    if (self->node1 == NULL)
    {
        /* head status */
        self->node0 = node->next;   /* move iterator node */
        if (head != NULL)
            *head = node->next;         /* update head */
    }
    else
    {
        /* normal status */
        self->node1->next = node->next;  /* delete next node */
        self->node0 = node->next;       /* restore initial status */
    }
    
    return node;
}

/**
 * Insert new node to current position.
 * 
 * Iterator will be reset, call next() before next action.
 * 
 * @param self: the ListIter object pointer.
 * @param node: the node to be insert.
 * @param head: the head pointer which be may updated after removal. 
 *      Or NULL if don't care.
 * 
 * @return a pointer to insert node, or NULL if failed.
 */
List *ListIter_insert(ListIter *self, List *node, List **head)
{
    if (self->node0 == self->node1)
    {
        /* initial status */
        return NULL;
    }

    /* link node before node0, */
    node->next = self->node0;

    if (self->node1 == NULL)
    {
        /* head */
        if (head != NULL)
            *head = node;
    }
    else
    {
        /* normal or end */
        self->node1->next = node;
    }
    self->node0 = node;

    return node;
}

/* ---------------------------------------------------------------------------
 *  DoubleListIter implements
 * ------------------------------------------------------------------------ */

/**
 * Init list iterator by double list head.
 * 
 * @param self: the ListIter object to be init.
 * @param head: the head of double list.
 */
void DoubleListIter_init(ListIter *self, DoubleList *head)
{

}

/**
 * Move iterator to next node.
 * 
 * @param self: the ListIter object pointer.
 */
void DoubleListIter_next(ListIter *self)
{

}

/**
 * Get current double list node.
 * 
 * @param self: the ListIter object pointer.
 * 
 * @return a pointer to current double list.
 */
List *DoubleListIter_current(ListIter *self)
{
    return NULL;
}

/**
 * Remove current item from double list.
 * 
 * @param self: the ListIter object pointer.
 * @param head: the head pointer which be may updated after removal. 
 *      Or NULL if don't care.
 * 
 * @return a pointer to removed node.
 */
DoubleList *DoubleListIter_remove(ListIter *self, DoubleList **head)
{
    return NULL;
}

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
List *DoubleListIter_insert(ListIter *self, DoubleList *node, DoubleList **head)
{
    return NULL;
}


