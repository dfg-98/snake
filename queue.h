#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct  node
{
    int x, y;
    int d;
    struct node *parent;
    struct node *next;
    
} node_t;



typedef struct queue
{
    int count;
    node_t *head;
    node_t *tail;
} queue_t;

queue_t init_queue();
void delete_queue(queue_t *queue);
void enqueue(queue_t *queue, node_t *node);
node_t *dequeue(queue_t *queue);



#endif
