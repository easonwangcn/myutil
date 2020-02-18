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
 * @file double_list.c
 * @author Eason Wang, talktoeason@gmail.com
 */

#include "myutil.h"

/**
 * Move iterator to next node.
 * 
 * @param self: the ListIter object pointer.
 * @return a booean, false for iterator reaches the end, otherwise true.
 */
bool DbListIter_next(DbListIter *self)
{
    if (self->head == NULL)
    {
        /* initial status or empty */
        self->head = self->current;
        return self->current != NULL;
    }

    if (self->current->next == self->head)
    {
        /* end */
        return false;
    }

    /* move to next */
    self->current = self->current->next;
    return true;
}

/**
 * Move iterator to previouse node.
 * 
 * @param self: the ListIter object pointer.
 * @return a booean, false for iterator reaches the end, otherwise true.
 */
bool DbListIter_prev(DbListIter *self)
{
    if (self->current == self->head)
    {
        /* head or empty */
        return false;
    }
    
    if (self->head == NULL)
    {
        /* initial status */
        self->head = self->current;
        /* do not return */
    }
    
    /* move previous */
    self->current = self->current->prev;
    return true;
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
DbList *DbListIter_remove(DbListIter *self, DbList **head)
{
    if (self->head == NULL && !DbListIter_next(self))
    {
        /* inital status, or empty */
        return NULL;
    }

    DbList *node = self->current;
    if (node->next == node)
    {
        /* the only one. */
        self->head = self->current = NULL;
        if (head != NULL)
            *head = NULL;
        return node;
    }

    /* remove node from list. */
    node->prev->next = node->next;
    node->next->prev = node->prev;

    /* move iter to next. */
    self->current = node->next;

    if (self->head == node)
    {
        /* head */
        self->head = self->current;
        if (head != NULL)
            *head = self->head;
    }

    return node;
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
DbList *DbListIter_insert(DbListIter *self, DbList *node, DbList **head)
{
    if (self->head == NULL && !DbListIter_next(self))
    {
        /* inital status, no item in list. */
        DbList_init(node);
        self->current = node;
        self->head = self->current;
        return node;
    }

    DbList *current = self->current;
    DbList *prev = current->prev;

    /* link node to double list. */
    prev->next = node;
    node->prev = prev;
    node->next = current;
    current->prev = node;
    
    if (self->head == current)
    {
        /* head */
        if (head == NULL)
        {
            /* if head is not specified, insert node in tail. Do not move
             iterator. */
            return node;
        }
        else
        {
            /* move head to new node. */
            self->head = node;
            *head = node;
        }
    }

    /* move current to node */
    self->current = node;
    return node;
}
