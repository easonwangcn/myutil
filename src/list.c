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
 * Move iterator to next node.
 * 
 * @param self: the ListIter object pointer.
 */
bool ListIter_next(ListIter *self)
{
    if (self->current == NULL)
    {
        /* at the end */
        return false;
    }
    
    if (self->current == self->prev)
    {
        /* initial status, move to first one */
        self->prev = NULL;
    }
    else
    {
        /* move to next node */
        self->prev = self->current;
        self->current = self->current->next;
    }
    
    return self->current != NULL;
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
    if (self->current == NULL || 
        (self->current == self->prev && !ListIter_next(self)))
    {
        /* initial status or end */
        return NULL;
    }

    List *node = self->current;
    if (self->prev == NULL)
    {
        /* head status */
        self->current = node->next;   /* move iterator node */
        if (head != NULL)
            *head = node->next;         /* update head */
    }
    else
    {
        /* normal status */
        self->prev->next = node->next;  /* delete next node */
        self->current = node->next;       /* restore initial status */
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
    if (self->current == self->prev && !ListIter_next(self))
    {
        /* initial status */
        return NULL;
    }

    /* link node before current, */
    node->next = self->current;

    if (self->prev == NULL)
    {
        /* head */
        if (head != NULL)
            *head = node;
    }
    else
    {
        /* normal or end */
        self->prev->next = node;
    }
    self->current = node;

    return node;
}
