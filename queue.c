/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL)
        return false;
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q) {
        if (q->head)  // if queue has head
        {
            list_ele_t *tmp = q->head, *tmp2 = q->head->next;
            while (tmp2) {
                if (tmp->value)
                    free(tmp->value);
                free(tmp);
                tmp = tmp2;
                tmp2 = tmp2->next;
            }
            if (tmp->value)
                free(tmp->value);
            free(tmp);
        }
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
        return false;
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->value = malloc(strlen(s) + 1);
    if (newh->value == NULL) {
        free(newh);
        return false;
    }

    strcpy(newh->value, s);
    newh->next = q->head;
    q->head = newh;
    q->size++;
    if (q->size == 1)
        q->tail = q->head;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || s == NULL)
        return false;
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;
    newt->value = malloc(strlen(s) + 1);
    if (newt->value == NULL) {
        free(newt);
        return false;
    }
    strcpy(newt->value, s);
    if (q->tail)
        q->tail->next = newt;
    q->tail = newt;
    newt->next = NULL;
    q->size++;
    if (q->size == 1)
        q->head = q->tail;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL)
        return false;

    if (sp) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_ele_t *tmp = q->head;

    if (q->head->next)
        q->head = q->head->next;
    else
        q->head = NULL;
    if (tmp->value)
        free(tmp->value);
    free(tmp);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q)
        return q->size;
    else
        return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL)
        return;
    list_ele_t *tmp = q->head->next;
    q->tail = q->head;
    while (tmp) {
        q->tail->next = tmp->next;
        tmp->next = q->head;
        q->head = tmp;
        tmp = q->tail->next;
    }
    /* You need to write the code for this function */
}
