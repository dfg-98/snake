#include "queue.h"

#include <stdlib.h>

queue_t init_queue(void)
{
    queue_t q;
    q.head = NULL;
    q.tail = NULL;
    q.count = 0;
    return q;
}

void delete_queue(queue_t *q)
{
    while (q->head) {
        node_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp);
    }
    q->tail = NULL;
    q->count = 0;
}

void enqueue(queue_t *q, node_t *n)
{
    n->next = NULL;
    if (q->head == NULL) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
    q->count++;
}

node_t *dequeue(queue_t *q)
{
    if (q->head == NULL) {
        return NULL;
    }
    node_t *n = q->head;
    q->head = q->head->next;
    q->count--;
    return n;
}

void destroy_bfs_queue(queue_t *q)
{
    while (q->head) {
        node_t *current = q->head;
        while (current->parent != NULL) {
            node_t *tmp = current->parent;
            current = tmp->parent;
            free(tmp);
        }
        node_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp);
    }
    q->tail = NULL;
    q->count = 0;
}